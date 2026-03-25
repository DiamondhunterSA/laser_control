import os
import time
import traceback

import cv2
import numpy as np

from power_test import connect_power_meter, measure_power, close_power_meter

from laser_shutter import init_shutter, send_shutter_command, close_shutter
from devices_camera import (
    list_cameras,
    runccd_realtime,
    save_frame_with_timestamp,
    put_chinese_text,
)
from devices_stage import (
    init_sdk,
    connect_to_controller,
    disconnect_controller,
    get_stage_position,
    get_stage_zposition,
    move_stage_speed,
    cmd,
)
from autofocus_workflows import (
    AutoFocusWithDisplay,
    auto_focus_with_display,
    auto_focus_refine_with_display,
    quick_auto_focus,
)
from autowork import (
    collect_ablation_loop_config,
    run_one_click_ablation_loop,
    get_current_z_from_stage,
)


def parse_current_z(default_z=0):
    error_code, z_response = get_stage_zposition()
    if error_code != 0:
        print(f"获取Z位置失败: {z_response}")
        return default_z

    try:
        return int(z_response.strip())
    except ValueError:
        print(f"无法解析Z位置: {z_response}")
        return default_z


def handle_realtime_mode(camera_list):
    print("\n进入实时显示模式...")
    try:
        camera_index = int(input(f"选择相机索引 (0-{len(camera_list) - 1}): "))
    except ValueError:
        camera_index = 0
    runccd_realtime(camera_index)


def handle_autofocus_mode(current_z, camera_list):
    print("\n进入自动对焦模式（完整搜索）...")

    try:
        start_z = int(input(f"起始Z位置 (默认 {current_z}): ") or current_z)
        search_range = int(input("搜索范围 (默认 200): ") or 200)
        step = int(input("搜索步长 (默认 10): ") or 10)

        display_choice = input("是否显示实时图像? (y/n, 默认 y): ").strip().lower()
        display_enabled = display_choice != "n"

        save_choice = input("是否保存所有测试图像? (y/n, 默认 n): ").strip().lower()
        save_images = save_choice == "y"

        camera_index = int(input(f"选择相机索引 (0-{len(camera_list) - 1}): ") or 0)
    except ValueError:
        print("输入无效，使用默认值")
        start_z = current_z
        search_range = 200
        step = 10
        display_enabled = True
        save_images = False
        camera_index = 0

    print("\n自动对焦参数:")
    print(f"起始位置: {start_z}")
    print(f"搜索范围: {search_range}")
    print(f"步长: {step}")
    print(f"显示图像: {'是' if display_enabled else '否'}")
    print(f"保存图像: {'是' if save_images else '否'}")

    input("\n按回车键开始自动对焦...")

    best_z, best_sharpness, _ = auto_focus_with_display(
        start_z,
        search_range,
        step,
        camera_index,
        display_enabled,
        save_images,
    )

    refine_choice = input("\n是否执行精细对焦? (y/n): ").strip().lower()
    if refine_choice == "y":
        refine_range = int(input("精细搜索范围 (默认 50): ") or 50)
        fine_step = int(input("精细搜索步长 (默认 2): ") or 2)

        refined_z, refined_sharpness = auto_focus_refine_with_display(
            best_z,
            refine_range,
            fine_step,
            camera_index,
        )

        print("\n最终对焦结果:")
        print(f"  Z位置: {refined_z}")
        print(f"  清晰度: {refined_sharpness}")
        return refined_z

    print("\n最终对焦结果:")
    print(f"  Z位置: {best_z}")
    print(f"  清晰度: {best_sharpness}")
    return best_z


def handle_quick_autofocus(current_z, camera_list):
    print("\n进入快速自动对焦测试...")

    try:
        start_z = int(input(f"起始Z位置 (默认 {current_z}): ") or current_z)
        num_positions = int(input("测试位置数量 (默认 5): ") or 5)
        camera_index = int(input(f"选择相机索引 (0-{len(camera_list) - 1}): ") or 0)
    except ValueError:
        print("输入无效，使用默认值")
        start_z = current_z
        num_positions = 5
        camera_index = 0

    input("\n按回车键开始...")
    best_z, best_sharpness = quick_auto_focus(start_z, camera_index, num_positions)

    print("\n快速对焦结果:")
    print(f"  Z位置: {best_z}")
    print(f"  清晰度: {best_sharpness}")
    return best_z


def handle_test_screenshot():
    print("\n测试截图功能...")
    test_image = np.zeros((400, 400, 3), dtype=np.uint8)
    test_image = put_chinese_text(test_image, "测试图像", (100, 200), text_size=40)

    saved_path = save_frame_with_timestamp(test_image, "test_image")
    if saved_path and os.path.exists(saved_path):
        print(f"测试成功！文件已创建: {saved_path}")
        print(f"文件大小: {os.path.getsize(saved_path)} 字节")
        cv2.imshow("测试图像", test_image)
        cv2.waitKey(2000)
        cv2.destroyAllWindows()
    else:
        print("测试失败！")


def capture_laser_result_image(x_feedrate, avg_power=None, camera_index=0):
    af = AutoFocusWithDisplay(camera_index)
    af.display_enabled = True
    af.save_images = False

    if not af.open_camera():
        print("无法打开相机拍照")
        return

    try:
        time.sleep(0.5)
        mat, _ = af.capture_with_display(z_position=0, delay_ms=2000)
        if mat is None:
            return

        error_code, xy_final = get_stage_position()
        if error_code == 0:
            _, y_final = map(float, xy_final.split(","))
        else:
            y_final = 0.0
            print("获取XY位置失败，使用默认值(0,0)")

        z_error_code, z_response = get_stage_zposition()
        if z_error_code == 0:
            try:
                z_final = float(z_response.strip())
            except ValueError:
                z_final = 0.0
                print(f"无法解析Z位置，使用默认值0: {z_response}")
        else:
            z_final = 0.0
            print("获取Z位置失败，使用默认值0")

        filename_parts = [f"laser_line_X{x_feedrate:.0f}_Y{y_final:.0f}_Z{z_final:.0f}"]
        if avg_power is not None:
            filename_parts.append(f"P{avg_power:.4f}W")

        filename = "_".join(filename_parts)
        saved_path = save_frame_with_timestamp(mat, filename)
        if saved_path:
            print(f"照片已保存: {saved_path}")

        cv2.imshow("激光划线结果", mat)
        cv2.waitKey(3000)
        cv2.destroyAllWindows()
    finally:
        af.close()


def handle_laser_line_task():
    powermeter = connect_power_meter(0)
    if powermeter is None:
        print("未能连接功率计，划线将不记录功率")

    try:
        for x_feedrate in range(20, 520, 5):
            power_samples = []
            avg_power = None

            error_code, xy_response = get_stage_position()
            if error_code == 0:
                x_current, _ = map(float, xy_response.split(","))
            else:
                x_current = 0.0
                print("获取XY位置失败，使用默认值(0,0)")

            line_length = 50.0

            print("打开激光器...")
            send_shutter_command("open")

            print("开始划线...")
            #_ = x_current - line_length
            move_stage_speed(x_feedrate, 0)
            start_time = time.time()

            while True:
                if powermeter is not None:
                    power_value = measure_power(powermeter)
                    if power_value is not None:
                        power_samples.append(power_value)

                busy_code, response = cmd("controller.stage.busy.get", verbose=False)
                if busy_code == 0 and response.strip() == "0":
                    break

                timeout_limit = line_length / x_feedrate + 5.0
                if time.time() - start_time > timeout_limit:
                    print("等待划线完成超时，强制退出测量循环")
                    break

                time.sleep(0.1)

            move_stage_speed(0, 0)
            send_shutter_command("close")

            if power_samples:
                avg_power = sum(power_samples) / len(power_samples)
                print(f"本次划线平均功率: {avg_power:.4f} W")
            else:
                print("未获取到功率数据")

            print("激光烧蚀完成，开始自动截图...")
            time.sleep(2)
            capture_laser_result_image(x_feedrate, avg_power, camera_index=0)

        print("\n激光划线任务完成！")
    except Exception as e:
        print(f"激光划线流程出错: {e}")
        traceback.print_exc()
    finally:
        if powermeter is not None:
            close_power_meter(powermeter)


def handle_one_click_ablation_loop_task(current_z):
    print("\n进入功能7：一键烧蚀循环...")

    stage_z = get_current_z_from_stage(default_z=current_z)
    cfg = collect_ablation_loop_config(stage_z)

    input("\n按回车键开始执行功能7...")
    rounds_done, end_z = run_one_click_ablation_loop(cfg, capture_callback=capture_laser_result_image)
    print(f"功能7完成：总轮次={rounds_done}, 结束Z={end_z:.2f}")
    return int(end_z)


def main():
    print("=" * 60)
    print("CCD相机自动对焦系统（拆分版）")
    print("=" * 60)

    print("\n1. 初始化移动平台SDK...")
    if not init_sdk():
        print("移动平台SDK初始化失败，退出程序")
        return

    print("\n2. 连接移动平台...")
    connect_error, connect_response = connect_to_controller(3)
    if connect_error != 0:
        print(f"连接移动平台失败: {connect_response}")
        return

    print("\n3. 初始化激光快门...")
    if init_shutter(port="COM4"):
        send_shutter_command("close")
    else:
        print("快门初始化失败，后续快门操作可能不可用")

    print("\n4. 检测相机设备...")
    camera_list = list_cameras()
    if not camera_list:
        print("未找到相机设备，退出程序")
        return

    current_z = parse_current_z(default_z=0)
    print(f"当前Z位置: {current_z}")

    try:
        while True:
            print("\n" + "=" * 60)
            print("请选择操作模式:")
            print("1. 实时显示模式 (手动观察)")
            print("2. 自动对焦模式（完整搜索）")
            print("3. 快速自动对焦测试")
            print("4. 测试截图功能")
            print("5. 激光直线烧蚀")
            print("6. 退出程序")
            print("7. 一键烧蚀循环")
            print("=" * 60)

            choice = input("请输入选项 (1-7): ").strip()

            if choice == "1":
                handle_realtime_mode(camera_list)
            elif choice == "2":
                current_z = handle_autofocus_mode(current_z, camera_list)
            elif choice == "3":
                current_z = handle_quick_autofocus(current_z, camera_list)
            elif choice == "4":
                handle_test_screenshot()
            elif choice == "5":
                handle_laser_line_task()
            elif choice == "6":
                print("退出程序...")
                break
            elif choice == "7":
                current_z = handle_one_click_ablation_loop_task(current_z)
            else:
                print("无效选项，请重新输入")
    finally:
        print("\n断开移动平台连接...")
        disconnect_controller()
        close_shutter()
        cv2.destroyAllWindows()


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n用户中断程序")
    except Exception as e:
        print(f"\n程序执行出错: {e}")
        traceback.print_exc()
    finally:
        print("\n程序结束")
