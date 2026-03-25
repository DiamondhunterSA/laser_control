import time
from dataclasses import dataclass

from devices_stage import (
    cmd,
    get_stage_zposition,
    move_stage_speed,
    move_stage_relative,
    move_stage_zabsolute,
    wait_stage_idle,
    wait_z_idle,
)
from laser_shutter import send_shutter_command
from power_test import connect_power_meter, measure_power, close_power_meter


@dataclass
class AblationLoopConfig:
    x_feedrate: float
    line_length: float
    y_step: float
    z_step_abs: float
    target_z: float
    camera_index: int = 0
    capture_each_round: bool = True
    enable_power_meter: bool = True
    y_positive_is_down: bool = True
    z_raise_is_negative: bool = True
    max_rounds: int = 200
    sample_interval_s: float = 0.1
    timeout_margin_s: float = 5.0


def _ask_float(prompt_text, default_value):
    raw = input(prompt_text).strip()
    if raw == "":
        return float(default_value)
    return float(raw)


def _ask_int(prompt_text, default_value):
    raw = input(prompt_text).strip()
    if raw == "":
        return int(default_value)
    return int(raw)


def get_current_z_from_stage(default_z=0.0):
    error_code, z_response = get_stage_zposition()
    if error_code != 0:
        print(f"获取Z位置失败: {z_response}，使用默认值 {default_z}")
        return float(default_z)

    try:
        return float(z_response.strip())
    except ValueError:
        print(f"无法解析Z位置: {z_response}，使用默认值 {default_z}")
        return float(default_z)


def collect_ablation_loop_config(current_z):
    print("\n请输入一键烧蚀参数（回车使用默认值）")

    x_feedrate = _ask_float("烧蚀速度X feedrate (默认 120): ", 120)
    line_length = _ask_float("单条线长度 (默认 50): ", 50)
    y_step = _ask_float("每轮向下Y步长 (默认 5): ", 5)
    z_step_abs = _ask_float("每轮抬高Z步长绝对值 (默认 2): ", 2)
    target_z = _ask_float(f"目标Z停止值 (默认 {current_z - 20}): ", current_z - 20)
    camera_index = _ask_int("拍照相机索引 (默认 0): ", 0)

    power_choice = input("是否启用功率计采样? (y/n, 默认 y): ").strip().lower()
    enable_power_meter = power_choice != "n"

    capture_choice = input("是否每轮拍照? (y/n, 默认 y): ").strip().lower()
    capture_each_round = capture_choice != "n"

    max_rounds = _ask_int("最大轮次保护 (默认 200): ", 200)

    cfg = AblationLoopConfig(
        x_feedrate=x_feedrate,
        line_length=line_length,
        y_step=y_step,
        z_step_abs=abs(z_step_abs),
        target_z=target_z,
        camera_index=camera_index,
        capture_each_round=capture_each_round,
        enable_power_meter=enable_power_meter,
        y_positive_is_down=True,
        z_raise_is_negative=True,
        max_rounds=max_rounds,
    )

    print("\n参数确认:")
    print(f"  x_feedrate={cfg.x_feedrate}")
    print(f"  line_length={cfg.line_length}")
    print(f"  y_step={cfg.y_step} (当前约定: +Y 为下方)")
    print(f"  z_step_abs={cfg.z_step_abs} (当前约定: 抬高=Z减小)")
    print(f"  target_z={cfg.target_z}")
    print(f"  camera_index={cfg.camera_index}")
    print(f"  capture_each_round={'是' if cfg.capture_each_round else '否'}")
    print(f"  enable_power_meter={'是' if cfg.enable_power_meter else '否'}")
    print(f"  max_rounds={cfg.max_rounds}")

    return cfg


def _target_reached(current_z, target_z, z_raise_is_negative):
    if z_raise_is_negative:
        return current_z <= target_z
    return current_z >= target_z


def _single_line_ablation(cfg, powermeter):
    power_samples = []
    avg_power = None

    send_shutter_command("open")
    move_stage_speed(cfg.x_feedrate, 0)
    start_time = time.time()

    timeout_limit = cfg.line_length / max(abs(cfg.x_feedrate), 1e-6) + cfg.timeout_margin_s

    try:
        while True:
            if powermeter is not None:
                power_value = measure_power(powermeter)
                if power_value is not None:
                    power_samples.append(power_value)

            busy_code, response = cmd("controller.stage.busy.get", verbose=False)
            if busy_code == 0 and response.strip() == "0":
                break

            if time.time() - start_time > timeout_limit:
                print("等待单轮烧蚀完成超时，按保护逻辑停止当前轮")
                break

            time.sleep(cfg.sample_interval_s)
    finally:
        move_stage_speed(0, 0)
        send_shutter_command("close")

    if power_samples:
        avg_power = sum(power_samples) / len(power_samples)

    return avg_power


def _move_to_next_line(cfg, current_z):
    y_delta = abs(cfg.y_step) if cfg.y_positive_is_down else -abs(cfg.y_step)
    ret_y, msg_y = move_stage_relative(0, y_delta)
    if ret_y != 0:
        raise RuntimeError(f"Y方向移位失败: {msg_y}")
    wait_stage_idle(timeout=20.0)

    z_delta = -abs(cfg.z_step_abs) if cfg.z_raise_is_negative else abs(cfg.z_step_abs)
    next_z = current_z + z_delta

    if cfg.z_raise_is_negative and next_z < cfg.target_z:
        next_z = cfg.target_z
    if (not cfg.z_raise_is_negative) and next_z > cfg.target_z:
        next_z = cfg.target_z

    ret_z, msg_z = move_stage_zabsolute(next_z)
    if ret_z != 0:
        raise RuntimeError(f"Z轴移动失败: {msg_z}")
    wait_z_idle(timeout=20.0)

    return get_current_z_from_stage(default_z=next_z)


def run_one_click_ablation_loop(cfg, capture_callback=None):
    powermeter = None
    rounds_done = 0

    try:
        if cfg.enable_power_meter:
            powermeter = connect_power_meter(0)
            if powermeter is None:
                print("功率计连接失败，本次将不记录功率")

        current_z = get_current_z_from_stage(default_z=cfg.target_z)
        print(f"\n启动功能7一键烧蚀，当前Z={current_z:.2f}, 目标Z={cfg.target_z:.2f}")

        while (not _target_reached(current_z, cfg.target_z, cfg.z_raise_is_negative)) and rounds_done < cfg.max_rounds:
            rounds_done += 1
            print("\n" + "-" * 50)
            print(f"第 {rounds_done} 轮开始: Z={current_z:.2f}")

            avg_power = _single_line_ablation(cfg, powermeter)
            if avg_power is not None:
                print(f"第 {rounds_done} 轮平均功率: {avg_power:.4f} W")
            else:
                print(f"第 {rounds_done} 轮未获取到功率")

            if cfg.capture_each_round and capture_callback is not None:
                capture_callback(cfg.x_feedrate, avg_power, camera_index=cfg.camera_index)

            if _target_reached(current_z, cfg.target_z, cfg.z_raise_is_negative):
                break

            current_z = _move_to_next_line(cfg, current_z)
            print(f"第 {rounds_done} 轮结束，下一轮起始Z={current_z:.2f}")

        print("\n功能7流程结束")
        print(f"完成轮次: {rounds_done}")
        print(f"结束Z: {current_z:.2f}")
        return rounds_done, current_z
    finally:
        move_stage_speed(0, 0)
        send_shutter_command("close")
        if powermeter is not None:
            close_power_meter(powermeter)
