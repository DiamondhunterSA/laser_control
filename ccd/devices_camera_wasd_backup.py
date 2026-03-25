import os
import sys
import time
import importlib.util
import numpy as np
import cv2
from PIL import Image, ImageDraw, ImageFont

correct_sdk_path = r"D:\\ccd\\DVP2 SDK\\Sample\\Python\\lib\\windows\\python3.6\\x64"
if correct_sdk_path not in sys.path:
    sys.path.insert(0, correct_sdk_path)

current_system_path = os.environ.get("PATH", "")
if correct_sdk_path not in current_system_path:
    os.environ["PATH"] = correct_sdk_path + os.pathsep + current_system_path

from dvp import *
from laser_shutter import init_shutter, send_shutter_command
from devices_stage import cmd


def _load_z_relative_module():
    script_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "Z轴相对移动.py"))
    if not os.path.exists(script_path):
        return None

    spec = importlib.util.spec_from_file_location("z_axis_relative_move", script_path)
    if spec is None or spec.loader is None:
        return None

    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def put_chinese_text(img, text, position, text_color=(255, 255, 255), text_size=30):
    cv2_im = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    pil_im = Image.fromarray(cv2_im)
    draw = ImageDraw.Draw(pil_im)

    font_paths = [
        "msyh.ttc",
        "simhei.ttf",
        "C:\\Windows\\Fonts\\msyh.ttc",
        "C:\\Windows\\Fonts\\simhei.ttf",
    ]
    font = None
    for path in font_paths:
        try:
            font = ImageFont.truetype(path, text_size, encoding="utf-8")
            break
        except IOError:
            continue

    if font is None:
        cv2.putText(
            img,
            text.replace("Z位置", "Z Pos").replace("清晰度", "Sharpness").replace("测试图像", "Test Image"),
            position,
            cv2.FONT_HERSHEY_SIMPLEX,
            0.7,
            text_color,
            2,
        )
        return img

    draw.text(position, text, font=font, fill=text_color)
    return cv2.cvtColor(np.array(pil_im), cv2.COLOR_RGB2BGR)


def frame2mat(frameBuffer):
    frame, buffer = frameBuffer
    bits = np.uint8 if (frame.bits == Bits.BITS_8) else np.uint16

    if frame.format >= ImageFormat.FORMAT_MONO and frame.format <= ImageFormat.FORMAT_BAYER_RG:
        shape = 1
    elif frame.format == ImageFormat.FORMAT_BGR24 or frame.format == ImageFormat.FORMAT_RGB24:
        shape = 3
    elif frame.format == ImageFormat.FORMAT_BGR32 or frame.format == ImageFormat.FORMAT_RGB32:
        shape = 4
    else:
        return None

    mat = np.frombuffer(buffer, bits)
    mat = mat.reshape(frame.iHeight, frame.iWidth, shape)
    return mat


def set_camera_params(camera):
    roi = camera.Roi
    roi.X = 0
    roi.Y = 0
    roi.W = 400
    roi.H = 400
    camera.Roi = roi
    camera.ResolutionModeSel = 0
    camera.AeOperation = AeOperation.AE_OP_CONTINUOUS
    camera.AntiFlick = AntiFlick.ANTIFLICK_DISABLE
    camera.Contrast = 199
    camera.AeTarget = 135
    camera.AeMode = AeMode.AE_MODE_AE_ONLY
    camera.AwbOperation = AwbOperation.AWB_OP_CONTINUOUS


def list_cameras():
    cameraInfo = Refresh()
    if len(cameraInfo) == 0:
        print("没有找到相机设备")
        return []

    for k, v in enumerate(cameraInfo):
        print(f"{k} -> {v.FriendlyName}")
    return cameraInfo


def open_camera(camera_index=0):
    try:
        cameraInfo = Refresh()
        if len(cameraInfo) == 0:
            print("没有找到相机设备")
            return None

        if camera_index >= len(cameraInfo):
            print(f"无效的相机索引: {camera_index}")
            return None

        camera = Camera(camera_index)
        camera.TriggerState = False
        set_camera_params(camera)
        camera.Start()
        print(f"成功打开相机: {cameraInfo[camera_index].FriendlyName}")
        return camera
    except dvpException as e:
        print(f"打开相机失败: {e.Status}")
        return None
    except Exception as e:
        print(f"打开相机时发生错误: {e}")
        return None


def capture_image(camera, timeout=4000):
    try:
        frame = camera.GetFrame(timeout)
        return frame2mat(frame)
    except dvpException as e:
        if e.Status == Status.DVP_STATUS_TIME_OUT:
            print("捕获图像超时")
        else:
            print(f"采集图像数据失败: {e.Status}")
        return None
    except Exception as e:
        print(f"捕获图像时发生错误: {e}")
        return None


def close_camera(camera):
    try:
        camera.Stop()
        camera.Close()
        print("相机已关闭")
    except Exception as e:
        print(f"关闭相机时出错: {e}")


def runccd_realtime(camera_index=0, shutter_port="COM4", z_step_microns=2.0):
    camera = open_camera(camera_index)
    if camera is None:
        return

    shutter_ready = False
    shutter_is_open = False
    z_helper = _load_z_relative_module()
    last_z_read_time = 0.0
    current_z_text = "Z: --"
    z_step_min = 0.1
    z_step_max = 20.0
    z_step_delta = 0.5
    z_step_microns = max(z_step_min, min(z_step_max, float(z_step_microns)))

    print(
        "进入实时显示模式 "
        "(按ESC退出，按S保存，按L切换快门，方向键上/下移动Z轴，方向键左/右调步长)"
    )
    try:
        while True:
            mat = capture_image(camera)
            if mat is not None:
                now = time.time()
                if z_helper is not None and now - last_z_read_time >= 0.25:
                    z_um = z_helper.get_z_position_microns_with_cmd(cmd)
                    if z_um is not None:
                        current_z_text = f"Z: {z_um:.2f} um"
                    last_z_read_time = now

                overlay = put_chinese_text(mat.copy(), current_z_text, (10, 10), text_size=22)
                overlay = put_chinese_text(overlay, f"步长: {z_step_microns:.2f} um", (10, 40), text_size=22)
                cv2.imshow(
                    "实时显示 (按ESC退出，按S保存，按L切换快门，方向键上/下移动Z轴，方向键左/右调步长)",
                    overlay,
                )

            key = cv2.waitKeyEx(1)
            key_low = key & 0xFF

            if key_low == 27:
                break
            if key_low == ord("s") or key_low == ord("S"):
                if mat is not None:
                    save_frame_with_timestamp(mat, "realtime_screenshot")
            if key_low == ord("p") or key_low == ord("P"):
                cv2.waitKey(0)
            if key_low == ord("l") or key_low == ord("L"):
                if not shutter_ready:
                    shutter_ready = init_shutter(port=shutter_port)
                    if not shutter_ready:
                        print("快门初始化失败，无法执行开关")
                        continue

                target_command = "close" if shutter_is_open else "open"
                success = send_shutter_command(target_command)
                if success:
                    shutter_is_open = not shutter_is_open
                    print(f"快门状态: {'打开' if shutter_is_open else '关闭'}")

            if key == 2490368:  # Up arrow
                if z_helper is not None:
                    if z_helper.move_rel_microns_with_cmd(cmd, -abs(z_step_microns)):
                        z_um = z_helper.get_z_position_microns_with_cmd(cmd)
                        if z_um is not None:
                            current_z_text = f"Z: {z_um:.2f} um"
                        print(f"Z轴上移 {abs(z_step_microns):.2f} um")
                else:
                    print("未找到 Z轴相对移动.py，无法执行方向键控制")

            if key == 2621440:  # Down arrow
                if z_helper is not None:
                    if z_helper.move_rel_microns_with_cmd(cmd, abs(z_step_microns)):
                        z_um = z_helper.get_z_position_microns_with_cmd(cmd)
                        if z_um is not None:
                            current_z_text = f"Z: {z_um:.2f} um"
                        print(f"Z轴下移 {abs(z_step_microns):.2f} um")
                else:
                    print("未找到 Z轴相对移动.py，无法执行方向键控制")

            if key == 2424832:  # Left arrow
                new_step = max(z_step_min, z_step_microns - z_step_delta)
                if new_step != z_step_microns:
                    z_step_microns = new_step
                    print(f"Z步长减小为 {z_step_microns:.2f} um")
                else:
                    print(f"已到最小步长 {z_step_min:.2f} um")

            if key == 2555904:  # Right arrow
                new_step = min(z_step_max, z_step_microns + z_step_delta)
                if new_step != z_step_microns:
                    z_step_microns = new_step
                    print(f"Z步长增大为 {z_step_microns:.2f} um")
                else:
                    print(f"已到最大步长 {z_step_max:.2f} um")
    finally:
        cv2.destroyAllWindows()
        close_camera(camera)


def capture_single_image_auto(camera_index=0, timeout=4000):
    camera = open_camera(camera_index)
    if camera is None:
        return None

    try:
        return capture_image(camera, timeout)
    finally:
        close_camera(camera)


def save_frame_with_timestamp(mat, prefix="screenshot", save_dir=None):
    if save_dir is None:
        save_dir = os.path.join(os.getcwd(), "screenshots")

    if not os.path.exists(save_dir):
        os.makedirs(save_dir)

    timestamp = time.strftime("%Y%m%d_%H%M%S")
    filename = f"{prefix}_{timestamp}.png"
    full_path = os.path.join(save_dir, filename)

    try:
        if mat is None or not isinstance(mat, np.ndarray) or mat.size == 0:
            print("错误: 图像矩阵无效")
            return None

        success = cv2.imwrite(full_path, mat)
        if success:
            print(f"图像已保存: {full_path}")
            return full_path
        print(f"保存失败: {full_path}")
        return None
    except Exception as e:
        print(f"保存图像时出错: {e}")
        return None
