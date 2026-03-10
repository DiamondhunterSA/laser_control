import sys
import os
import numpy as np
import cv2
import time
import serial
from duijiao import calculate_sharpness
from PIL import Image, ImageDraw, ImageFont
from power_test import get_power, find_devices, connect_power_meter, measure_power, close_power_meter # 导入功率计相关函数

# ==================== 新增：解决中文乱码的辅助函数 ====================
def put_chinese_text(img, text, position, text_color=(255, 255, 255), text_size=30):
    cv2_im = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    pil_im = Image.fromarray(cv2_im)
    draw = ImageDraw.Draw(pil_im)
    
    # 自动寻找系统中文字体
    font_paths = [
        "msyh.ttc", "simhei.ttf", 
        "C:\\Windows\\Fonts\\msyh.ttc", "C:\\Windows\\Fonts\\simhei.ttf"
    ]
    font = None
    for path in font_paths:
        try:
            font = ImageFont.truetype(path, text_size, encoding="utf-8")
            break
        except IOError:
            continue
            
    if font is None:
        # 如果电脑里真没中文字体，退回使用全英文，防止显示问号
        print("警告: 未找到中文字体")
        cv2.putText(img, text.replace('Z位置', 'Z Pos').replace('清晰度', 'Sharpness').replace('测试图像', 'Test Image'), 
                    position, cv2.FONT_HERSHEY_SIMPLEX, 0.7, text_color, 2)
        return img
        
    draw.text(position, text, font=font, fill=text_color)
    return cv2.cvtColor(np.array(pil_im), cv2.COLOR_RGB2BGR)
# ======================================================================

# =======================激光快门==========================
# 配置串口参数
ser = serial.Serial(
    port='COM4',        # 串口号
    baudrate=9600,      # 波特率
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1           # 读超时时间（秒）
)

# 激光快门全局命令
GLOBAL_COMMANDS = {
    'open': 64,    # '@' 打开快门
    'close': 65,   # 'A' 关闭快门
    'trigger': 66, # 'B' 触发（开->关 或 关->开）
    'reset': 67,   # 'C' 复位（清除中断状态）
    'aux_enable': 68,  # 'D' 辅助输出置低
    'aux_disable': 69, # 'E' 辅助输出置高
    'gate_on': 70, # 'F' 门控开启
    'gate_off': 71  # 'G' 门控关闭
}

# 发送命令的函数
def send_shutter_command(command_name):
    if command_name in GLOBAL_COMMANDS:
        cmd_byte = GLOBAL_COMMANDS[command_name].to_bytes(1, 'big')
        ser.write(cmd_byte)
        print(f"已发送命令: {command_name} (字节: {cmd_byte.hex()})")
    else:
        print(f"未知命令: {command_name}")

# 功率计加载
# ... (省略功率计相关代码) ...

# =======================ccd加载======================
print(f"Python版本: {sys.version}")
correct_sdk_path = r"D:\ccd\DVP2 SDK\Sample\Python\lib\windows\python3.6\x64"
if correct_sdk_path not in sys.path:
    sys.path.insert(0, correct_sdk_path)
current_system_path = os.environ.get('PATH', '')
if correct_sdk_path not in current_system_path:
    os.environ['PATH'] = correct_sdk_path + os.pathsep + current_system_path
print(f"[配置信息] 模块搜索路径已添加: {correct_sdk_path}")
print(f"[配置信息] 系统DLL路径已添加: {correct_sdk_path}")
from dvp import *


# ==================== CCD相机相关函数 ====================
def frame2mat(frameBuffer):
    """将帧信息转换为numpy的矩阵对象"""
    frame, buffer = frameBuffer
    bits = np.uint8 if (frame.bits == Bits.BITS_8) else np.uint16
    shape = None

    if (frame.format >= ImageFormat.FORMAT_MONO and frame.format <= ImageFormat.FORMAT_BAYER_RG):
        shape = 1
    elif (frame.format == ImageFormat.FORMAT_BGR24 or frame.format == ImageFormat.FORMAT_RGB24):
        shape = 3
    elif (frame.format == ImageFormat.FORMAT_BGR32 or frame.format == ImageFormat.FORMAT_RGB32):
        shape = 4
    else:
        return None

    mat = np.frombuffer(buffer, bits)
    mat = mat.reshape(frame.iHeight, frame.iWidth, shape)
    return mat

def setCameraParams(camera):
    """设置ccd相机参数"""
    # 设置ROI
    roiDescr = camera.RoiDescr
    roi = camera.Roi
    roi.X = 0
    roi.Y = 0
    roi.W = 400
    roi.H = 400
    camera.Roi = roi
    camera.ResolutionModeSel = 0
    print("分辨率模式0")
    light = 135
    camera.AeOperation = AeOperation.AE_OP_CONTINUOUS
    camera.AntiFlick = AntiFlick.ANTIFLICK_DISABLE
    camera.Contrast = 199
    camera.AeTarget = light
    camera.AeMode = AeMode.AE_MODE_AE_ONLY
    camera.AwbOperation = AwbOperation.AWB_OP_CONTINUOUS
    camera.SaveConfig("example.ini")

def list_cameras():
    """列出所有可用相机"""
    cameraInfo = Refresh()
    if len(cameraInfo) == 0:
        print("没有找到相机设备")
        return []
    for k, v in enumerate(cameraInfo):
        print(f"{k} -> {v.FriendlyName}")
    return cameraInfo


def open_camera(camera_index=0):
    """
    打开指定索引的相机
    参数:
        camera_index: 相机索引号
    返回:
        camera: 相机对象，失败返回None
    """
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
        setCameraParams(camera)
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
    """
    从相机捕获一帧图像
    参数:
        camera: 相机对象
        timeout: 超时时间（毫秒）
    返回:
        mat: 图像矩阵，失败返回None
    """
    try:
        frame = camera.GetFrame(timeout)
        mat = frame2mat(frame)
        return mat
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
    """关闭相机"""
    try:
        camera.Stop()
        camera.Close()
        print("相机已关闭")
    except Exception as e:
        print(f"关闭相机时出错: {e}")

def runccd_realtime(camera_index=0):
    """
    实时显示模式 - 适合手动观察

    参数:
        camera_index: 相机索引号
    """
    camera = open_camera(camera_index)
    if camera is None:
        return
    print("进入实时显示模式 (按ESC退出，按S保存当前帧)")
    try:
        while True:
            mat = capture_image(camera)
            if mat is not None:
                cv2.imshow("实时显示 (按ESC退出，按S保存)", mat)

            key = cv2.waitKey(1) & 0xFF

            if key == 27:  # ESC键
                print("退出实时显示模式")
                break
            elif key == ord('s') or key == ord('S'):  # 按S键保存
                if mat is not None:
                    save_frame_with_timestamp(mat, "realtime_screenshot")
                    print("已保存当前帧")
            elif key == ord('p') or key == ord('P'):  # 按P键暂停
                print("暂停，按任意键继续...")
                cv2.waitKey(0)

    except KeyboardInterrupt:
        print("\n用户中断")
    except Exception as e:
        print(f"实时显示过程中出错: {e}")
    finally:
        cv2.destroyAllWindows()
        close_camera(camera)


def capture_single_image_auto(camera_index=0, timeout=4000):
    """
    自动捕获单张图像 - 适合编程控制
    参数:
        camera_index: 相机索引号
        timeout: 超时时间
    返回:
        mat: 图像矩阵，失败返回None
    """
    camera = open_camera(camera_index)
    if camera is None:
        return None

    try:
        mat = capture_image(camera, timeout)
        return mat
    finally:
        close_camera(camera)


# ==================== 图像保存函数 ====================
def save_frame_with_timestamp(mat, prefix="screenshot", save_dir=None):
    """
    保存图像带时间戳

    参数:
        mat: 图像矩阵
        prefix: 文件名前缀
        save_dir: 保存目录（None则使用默认目录）
    返回:
        full_path: 保存的完整路径
    """
    import time
    import os

    # 如果save_dir未指定，使用当前目录的screenshots子文件夹
    if save_dir is None:
        save_dir = os.path.join(os.getcwd(), "screenshots")

    # 确保目录存在
    if not os.path.exists(save_dir):
        os.makedirs(save_dir)
        print(f"创建保存目录: {save_dir}")

    timestamp = time.strftime("%Y%m%d_%H%M%S")
    filename = f"{prefix}_{timestamp}.png"
    full_path = os.path.join(save_dir, filename)

    try:
        # 检查图像是否有效
        if mat is None:
            print("错误: 图像矩阵为None")
            return None

        if not isinstance(mat, np.ndarray):
            print("错误: 图像不是numpy数组")
            return None

        if mat.size == 0:
            print("错误: 图像矩阵为空")
            return None

        # 保存图像
        success = cv2.imwrite(full_path, mat)

        if success:
            print(f"图像已保存: {full_path}")
            print(f"图像尺寸: {mat.shape}, 数据类型: {mat.dtype}")
            return full_path
        else:
            print(f"保存失败: {full_path}")
            return None

    except Exception as e:
        print(f"保存图像时出错: {e}")
        return None


# ==================== 移动平台相关函数 ====================
# 移动平台SDK加载
from ctypes import WinDLL, create_string_buffer

sdk_dir = r"D:\ccd\PriorSDK 2.0.0\x64"
dll_path = os.path.join(sdk_dir, "PriorScientificSDK.dll")

# 将SDK目录添加到系统PATH
if sdk_dir not in os.environ['PATH']:
    os.environ['PATH'] = sdk_dir + os.pathsep + os.environ['PATH']
print(f"SDK目录: {sdk_dir}")
print(f"DLL路径: {dll_path}")

# 检查DLL是否存在
if not os.path.exists(dll_path):
    print(f"错误: DLL文件不存在: {dll_path}")
    raise RuntimeError("DLL could not be loaded.")

try:
    SDKPrior = WinDLL(dll_path)
    print("✅ DLL加载成功!")
except Exception as e:
    print(f"❌ DLL加载失败: {e}")
    raise

# 全局变量
rx = create_string_buffer(1000)
sessionID = None


# 初始化SDK
def init_sdk():
    """初始化移动平台SDK"""
    global sessionID

    ret = SDKPrior.PriorScientificSDK_Initialise()
    if ret:
        print(f"初始化失败: {ret}")
        return False
    else:
        print("SDK初始化成功")

    ret = SDKPrior.PriorScientificSDK_Version(rx)
    print(f"DLL版本: {rx.value.decode()}")

    sessionID = SDKPrior.PriorScientificSDK_OpenNewSession()
    if sessionID < 0:
        print(f"获取sessionID失败: {sessionID}")
        return False
    else:
        print(f"SessionID = {sessionID}")

    return True


# SDK命令函数
def cmd(msg, verbose=True):
    """
    发送命令到移动平台

    参数:
        msg: 命令字符串
        verbose: 是否打印详细信息
    返回:
        (ret, response): 错误码和响应字符串
    """
    if verbose:
        print(f"发送命令: {msg}")

    ret = SDKPrior.PriorScientificSDK_cmd(
        sessionID, create_string_buffer(msg.encode()), rx
    )

    response = rx.value.decode()

    if verbose:
        if ret:
            print(f"API错误 {ret}: {response}")
        else:
            print(f"命令成功: {response}")

    return ret, response


# 连接控制器
def connect_to_controller(port):
    return cmd(f"controller.connect {port}")


# 断开控制器连接
def disconnect_controller():
    return cmd("controller.disconnect")


# 获取载物台当前位置
def get_stage_position():
    return cmd("controller.stage.position.get")


# 获取Z轴位置
def get_stage_zposition():
    return cmd("controller.z.position.get")


# 移动载物台到绝对坐标
def move_stage_absolute(x, y):
    return cmd(f"controller.stage.goto-position {x} {y}")


# 移动Z轴到绝对位置
def move_stage_zabsolute(z):
    return cmd(f"controller.z.goto-position {z}")


# 设置移动速度
def move_stage_speed(speed_x, speed_y):
    return cmd(f"controller.stage.move-at-velocity {speed_x} {speed_y}")


# 等待载物台空闲
def wait_stage_idle(timeout=10.0):
    start_time = time.time()
    while time.time() - start_time < timeout:
        error_code, response = cmd("controller.stage.busy.get", verbose=False)
        if error_code == 0 and response.strip() == "0":
            return True
        time.sleep(0.1)
    print("等待载物台空闲超时！")
    return False


# 等待Z轴空闲
def wait_z_idle(timeout=10.0):
    start_time = time.time()
    while time.time() - start_time < timeout:
        error_code, response = cmd("controller.z.busy.get", verbose=False)
        if error_code == 0 and response.strip() == "0":
            return True
        time.sleep(0.1)
    print("等待Z轴空闲超时！")
    return False


# ==================== 自动对焦函数 ====================
class AutoFocusWithDisplay:
    """带实时显示的自动对焦类"""

    def __init__(self, camera_index=0):
        self.camera_index = camera_index
        self.camera = None
        self.window_name = "自动对焦 - 实时显示"
        self.display_enabled = True
        self.save_images = False

    def open_camera(self):
        """打开相机"""
        try:
            cameraInfo = Refresh()
            if len(cameraInfo) == 0:
                print("没有找到相机设备")
                return None

            if self.camera_index >= len(cameraInfo):
                print(f"无效的相机索引: {self.camera_index}")
                return None

            self.camera = Camera(self.camera_index)
            self.camera.TriggerState = False

            # 设置相机参数
            roi = self.camera.Roi
            roi.X = 0
            roi.Y = 0
            roi.W = 400
            roi.H = 400
            self.camera.Roi = roi
            self.camera.ResolutionModeSel = 0
            self.camera.AeOperation = AeOperation.AE_OP_CONTINUOUS
            self.camera.AntiFlick = AntiFlick.ANTIFLICK_DISABLE
            self.camera.Contrast = 199
            self.camera.AeTarget = 135
            self.camera.AeMode = AeMode.AE_MODE_AE_ONLY
            self.camera.AwbOperation = AwbOperation.AWB_OP_CONTINUOUS
            self.camera.Start()
            print(f"成功打开相机: {cameraInfo[self.camera_index].FriendlyName}")
            return True
        except Exception as e:
            print(f"打开相机失败: {e}")
            return False

    def capture_with_display(self, z_position, sharpness=None, delay_ms=1000):
        """
        捕获并显示图像

        参数:
            z_position: 当前Z位置
            sharpness: 清晰度值
            delay_ms: 显示延迟时间（毫秒）
        返回:
            mat: 图像矩阵
            sharpness_val: 清晰度值
        """
        if self.camera is None:
            return None, 0

        try:
            # 捕获图像
            frame = self.camera.GetFrame(4000)
            mat = frame2mat(frame)

            if mat is not None:
                # 计算清晰度
                if sharpness is None:
                    sharpness_val = calculate_sharpness(mat)
                else:
                    sharpness_val = sharpness

                # 显示图像
                if self.display_enabled:
                    # 创建显示副本
                    display_img = mat.copy()

                    # ============ 替换为支持中文的显示逻辑 ============
                    display_img = put_chinese_text(display_img, f"Z位置: {z_position}", (10, 10), text_size=24)
                    
                    if sharpness_val is not None:
                        display_img = put_chinese_text(display_img, f"清晰度: {sharpness_val:.2f}", (10, 40), text_size=24)
                    # ==================================================

                    # 显示图像
                    cv2.imshow(self.window_name, display_img)

                    # 等待按键或延迟
                    key = cv2.waitKey(delay_ms) & 0xFF

                    # 处理按键
                    if key == 27:  # ESC键
                        print("用户中断自动对焦")
                        return None, sharpness_val
                    elif key == ord('s') or key == ord('S'):  # S键保存
                        save_frame_with_timestamp(mat, f"focus_z{z_position}")
                        print(f"已保存图像: Z={z_position}")
                    elif key == ord(' '):  # 空格键暂停
                        print("暂停，按任意键继续...")
                        cv2.waitKey(0)

                # 自动保存图像（如果启用）
                if self.save_images:
                    save_frame_with_timestamp(mat, f"auto_z{z_position}")

                return mat, sharpness_val

        except Exception as e:
            print(f"捕获/显示图像失败: {e}")

        return None, 0

    def close(self):
        """关闭资源"""
        if self.camera is not None:
            try:
                self.camera.Stop()
                self.camera.Close()
                print("相机已关闭")
            except:
                pass
        cv2.destroyAllWindows()


def auto_focus_with_display(start_z, search_range=200, step=10, camera_index=0,
                            display_enabled=True, save_images=True):
    """
    带实时显示的自动对焦搜索函数

    参数:
        start_z: 起始Z位置
        search_range: 搜索范围
        step: 搜索步长
        camera_index: 相机索引
        display_enabled: 是否启用显示
        save_images: 是否保存所有测试图像
    返回:
        best_z: 最佳Z位置
        best_sharpness: 最佳清晰度
        sharpness_data: 清晰度数据列表
    """
    print("开始自动对焦搜索（带实时显示）...")
    print(f"起始位置: z={start_z}, 搜索范围: ±{search_range}, 步长: {step}")

    # 创建自动对焦对象
    af = AutoFocusWithDisplay(camera_index)
    af.display_enabled = display_enabled
    af.save_images = save_images

    # 打开相机
    if not af.open_camera():
        print("无法打开相机")
        return start_z, 0, []

    try:
        # 计算搜索范围
        min_z = start_z - search_range
        max_z = start_z + search_range

        best_z = start_z
        best_sharpness = -1
        sharpness_data = []

        # 首先获取起始位置的图像
        print(f"\n测试起始位置 z={start_z}")

        # 移动到起始位置
        move_stage_zabsolute(start_z)
        if not wait_z_idle():
            print("移动Z轴失败")
            return start_z, 0, []

        time.sleep(0.5)  # 等待稳定

        # 捕获并显示起始图像
        print("正在捕获起始图像...")
        start_mat, initial_sharpness = af.capture_with_display(start_z, delay_ms=3000)

        if start_mat is None:
            print("捕获起始图像失败")
            return start_z, 0, []

        sharpness_data.append((start_z, initial_sharpness))
        best_sharpness = initial_sharpness
        print(f"起始位置清晰度: {initial_sharpness}")

        # 向前搜索（减少Z值）
        print("\n向前搜索...")
        current_z = start_z
        while current_z >= min_z:
            test_z = current_z - step
            if test_z < min_z:
                break

            print(f"测试位置 z={test_z}")

            # 移动到测试位置
            move_stage_zabsolute(test_z)
            if not wait_z_idle():
                print(f"移动失败，停止在 z={current_z}")
                break

            time.sleep(0.3)

            # 捕获并显示图像
            mat, sharpness = af.capture_with_display(test_z, delay_ms=1000)
            if mat is None:
                print("捕获图像失败或用户中断")
                break

            sharpness_data.append((test_z, sharpness))
            print(f"位置 z={test_z}, 清晰度: {sharpness}")

            # 更新最佳位置
            if sharpness > best_sharpness:
                best_sharpness = sharpness
                best_z = test_z
                print(f"更新最佳位置: z={best_z}, 清晰度={best_sharpness}")

            current_z = test_z

        # 向后搜索（增加Z值）
        print("\n向后搜索...")
        current_z = start_z
        while current_z <= max_z:
            test_z = current_z + step
            if test_z > max_z:
                break

            print(f"测试位置 z={test_z}")

            # 移动到测试位置
            move_stage_zabsolute(test_z)
            if not wait_z_idle():
                print(f"移动失败，停止在 z={current_z}")
                break

            time.sleep(0.3)

            # 捕获并显示图像
            mat, sharpness = af.capture_with_display(test_z, delay_ms=1000)
            if mat is None:
                print("捕获图像失败或用户中断")
                break

            sharpness_data.append((test_z, sharpness))
            print(f"位置 z={test_z}, 清晰度: {sharpness}")

            # 更新最佳位置
            if sharpness > best_sharpness:
                best_sharpness = sharpness
                best_z = test_z
                print(f"更新最佳位置: z={best_z}, 清晰度={best_sharpness}")

            current_z = test_z

        # 移动到最佳位置
        print(f"\n找到最佳位置: z={best_z}, 清晰度={best_sharpness}")
        print("移动到最佳位置...")

        move_stage_zabsolute(best_z)
        wait_z_idle()
        time.sleep(0.5)

        # 捕获最佳图像
        print("正在捕获最佳对焦图像...")
        best_mat, _ = af.capture_with_display(best_z, best_sharpness, delay_ms=5000)

        if best_mat is not None:
            # 保存最佳图像
            save_frame_with_timestamp(best_mat, f"best_focus_z{best_z}")
            print(f"已保存最佳对焦图像")

        return best_z, best_sharpness, sharpness_data

    except Exception as e:
        print(f"自动对焦过程中出错: {e}")
        import traceback
        traceback.print_exc()
        return start_z, 0, []
    finally:
        af.close()


def auto_focus_refine_with_display(best_z, refine_range=50, fine_step=2, camera_index=0):
    """
    带显示的精细对焦函数

    参数:
        best_z: 粗略最佳Z位置
        refine_range: 精细搜索范围
        fine_step: 精细搜索步长
        camera_index: 相机索引
    返回:
        refined_z: 精细调整后的最佳Z位置
        refined_sharpness: 精细调整后的最佳清晰度
    """
    print(f"\n开始精细对焦...")
    print(f"中心位置: z={best_z}, 搜索范围: ±{refine_range}, 步长: {fine_step}")

    # 创建自动对焦对象
    af = AutoFocusWithDisplay(camera_index)
    af.display_enabled = True

    # 打开相机
    if not af.open_camera():
        print("无法打开相机")
        return best_z, 0

    try:
        refined_z = best_z
        refined_sharpness = -1

        # 搜索范围
        min_z = best_z - refine_range
        max_z = best_z + refine_range

        # 从中心向两边搜索
        for direction in [-1, 1]:  # -1: 向下搜索, 1: 向上搜索
            current_z = best_z
            while True:
                test_z = current_z + direction * fine_step

                # 检查是否超出范围
                if test_z < min_z or test_z > max_z:
                    break

                print(f"精细测试位置 z={test_z}")

                # 移动到测试位置
                move_stage_zabsolute(test_z)
                if not wait_z_idle():
                    print("移动失败")
                    break

                time.sleep(0.2)

                # 捕获并显示图像
                mat, sharpness = af.capture_with_display(test_z, delay_ms=1500)
                if mat is None:
                    print("捕获图像失败或用户中断")
                    break

                print(f"位置 z={test_z}, 清晰度: {sharpness}")

                # 更新最佳位置
                if sharpness > refined_sharpness:
                    refined_sharpness = sharpness
                    refined_z = test_z
                    print(f"更新精细最佳位置: z={refined_z}, 清晰度={refined_sharpness}")

                current_z = test_z

        print(f"\n精细对焦完成!")
        print(f"精细最佳位置: z={refined_z}, 清晰度={refined_sharpness}")

        # 移动到精细最佳位置
        move_stage_zabsolute(refined_z)
        wait_z_idle()
        time.sleep(0.5)

        # 捕获最佳图像
        print("正在捕获最终对焦图像...")
        final_mat, _ = af.capture_with_display(refined_z, refined_sharpness, delay_ms=5000)

        if final_mat is not None:
            save_frame_with_timestamp(final_mat, f"final_focus_z{refined_z}")
            print(f"已保存最终对焦图像")

        return refined_z, refined_sharpness

    except Exception as e:
        print(f"精细对焦过程中出错: {e}")
        import traceback
        traceback.print_exc()
        return best_z, 0
    finally:
        af.close()


# ==================== 简化的自动对焦函数（快速测试） ====================
def quick_auto_focus(start_z, camera_index=0, num_positions=5):
    """
    快速自动对焦测试

    参数:
        start_z: 起始Z位置
        camera_index: 相机索引
        num_positions: 测试位置数量
    返回:
        best_z: 最佳Z位置
        best_sharpness: 最佳清晰度
    """
    print("快速自动对焦测试...")

    # 创建自动对焦对象
    af = AutoFocusWithDisplay(camera_index)
    af.display_enabled = True

    # 打开相机
    if not af.open_camera():
        print("无法打开相机")
        return start_z, 0

    try:
        best_z = start_z
        best_sharpness = -1

        # 测试几个位置
        test_positions = []
        for i in range(num_positions):
            offset = (i - num_positions // 2) * 50  # 在中心附近测试
            test_positions.append(start_z + offset)

        print(f"测试位置: {test_positions}")

        for i, test_z in enumerate(test_positions):
            print(f"\n测试位置 {i + 1}/{num_positions}: z={test_z}")

            # 移动到测试位置
            move_stage_zabsolute(test_z)
            if not wait_z_idle():
                print("移动失败，跳过此位置")
                continue

            time.sleep(0.3)

            # 捕获并显示图像
            mat, sharpness = af.capture_with_display(test_z, delay_ms=2000)
            if mat is None:
                print("捕获图像失败或用户中断")
                break

            print(f"清晰度: {sharpness}")

            # 更新最佳位置
            if sharpness > best_sharpness:
                best_sharpness = sharpness
                best_z = test_z
                print(f"更新最佳位置: z={best_z}, 清晰度={best_sharpness}")

        print(f"\n快速测试完成!")
        print(f"最佳位置: z={best_z}, 清晰度={best_sharpness}")

        # 移动到最佳位置
        move_stage_zabsolute(best_z)
        wait_z_idle()
        time.sleep(0.5)

        # 显示最终图像
        print("显示最终对焦图像...")
        final_mat, _ = af.capture_with_display(best_z, best_sharpness, delay_ms=5000)

        if final_mat is not None:
            save_frame_with_timestamp(final_mat, f"quick_focus_z{best_z}")
            print(f"已保存最终图像")

        return best_z, best_sharpness

    except Exception as e:
        print(f"快速对焦过程中出错: {e}")
        import traceback
        traceback.print_exc()
        return start_z, 0
    finally:
        af.close()


# ==================== 主函数 ====================
if __name__ == "__main__":
    try:
        print("=" * 60)
        print("CCD相机自动对焦系统（带实时显示）")
        print("=" * 60)

        # 1. 初始化移动平台SDK
        print("\n1. 初始化移动平台SDK...")
        if not init_sdk():
            print("移动平台SDK初始化失败，退出程序")
            exit(1)

        # 2. 连接移动平台
        print("\n2. 连接移动平台...")
        connect_error, connect_response = connect_to_controller(3)
        if connect_error != 0:
            print(f"连接移动平台失败: {connect_response}")
            exit(1)
        print("移动平台连接成功")

        # 3. 获取当前Z位置
        print("\n3. 获取当前位置...")
        error_code, z_response = get_stage_zposition()
        if error_code != 0:
            print(f"获取Z位置失败: {z_response}")
            current_z = 0
        else:
            try:
                current_z = int(z_response.strip())
                print(f"当前Z位置: {current_z}")
            except ValueError:
                print(f"无法解析Z位置: {z_response}")
                current_z = 0

        # 4. 关闭激光快门（可选）
        print("\n4. 关闭激光快门...")

        send_shutter_command('close')
        print("激光快门已关闭")


        # 5. 列出可用相机
        print("\n5. 检测相机设备...")
        camera_list = list_cameras()
        if not camera_list:
            print("未找到相机设备，退出程序")
            exit(1)

        # 6. 用户选择操作模式
        print("\n" + "=" * 60)
        print("请选择操作模式:")
        print("1. 实时显示模式 (手动观察)")
        print("2. 自动对焦模式（完整搜索）")
        print("3. 快速自动对焦测试")
        print("4. 测试截图功能")
        print("5. 激光直线烧蚀")
        print("6. 退出程序")
        print("=" * 60)

        choice = input("请输入选项 (1-5): ").strip()

        if choice == "1":
            # 实时显示模式
            print("\n进入实时显示模式...")
            try:
                camera_index = int(input(f"选择相机索引 (0-{len(camera_list) - 1}): "))
            except ValueError:
                camera_index = 0

            runccd_realtime(camera_index)

        elif choice == "2":
            # 自动对焦模式（完整搜索）
            print("\n进入自动对焦模式（完整搜索）...")

            # 获取参数
            try:
                start_z = int(input(f"起始Z位置 (默认 {current_z}): ") or current_z)
                search_range = int(input("搜索范围 (默认 200): ") or 200)
                step = int(input("搜索步长 (默认 10): ") or 10)

                # 显示选项
                display_choice = input("是否显示实时图像? (y/n, 默认 y): ").strip().lower()
                display_enabled = display_choice != 'n'

                save_choice = input("是否保存所有测试图像? (y/n, 默认 n): ").strip().lower()
                save_images = save_choice == 'y'

                # 选择相机
                camera_index = int(input(f"选择相机索引 (0-{len(camera_list) - 1}): ") or 0)
            except ValueError:
                print("输入无效，使用默认值")
                start_z = current_z
                search_range = 200
                step = 10
                display_enabled = True
                save_images = False
                camera_index = 0

            print(f"\n开始自动对焦...")
            print(f"起始位置: {start_z}")
            print(f"搜索范围: ±{search_range}")
            print(f"步长: {step}")
            print(f"显示图像: {'是' if display_enabled else '否'}")
            print(f"保存图像: {'是' if save_images else '否'}")

            input("\n按回车键开始自动对焦...")

            # 执行自动对焦
            best_z, best_sharpness, sharpness_data = auto_focus_with_display(
                start_z, search_range, step, camera_index,
                display_enabled, save_images
            )

            # 询问是否执行精细对焦
            refine_choice = input("\n是否执行精细对焦? (y/n): ").strip().lower()
            if refine_choice == 'y':
                refine_range = int(input("精细搜索范围 (默认 50): ") or 50)
                fine_step = int(input("精细搜索步长 (默认 2): ") or 2)

                refined_z, refined_sharpness = auto_focus_refine_with_display(
                    best_z, refine_range, fine_step, camera_index
                )

                print(f"\n最终对焦结果:")
                print(f"  Z位置: {refined_z}")
                print(f"  清晰度: {refined_sharpness}")
            else:
                print(f"\n最终对焦结果:")
                print(f"  Z位置: {best_z}")
                print(f"  清晰度: {best_sharpness}")

        elif choice == "3":
            # 快速自动对焦测试
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

            print(f"\n开始快速自动对焦...")
            print(f"起始位置: {start_z}")
            print(f"测试位置数量: {num_positions}")

            input("\n按回车键开始...")

            best_z, best_sharpness = quick_auto_focus(
                start_z, camera_index, num_positions
            )

            print(f"\n快速对焦结果:")
            print(f"  Z位置: {best_z}")
            print(f"  清晰度: {best_sharpness}")

        elif choice == "4":
            # 测试截图功能
            print("\n测试截图功能...")

            # 创建一个测试图像
            test_image = np.zeros((400, 400, 3), dtype=np.uint8)
            # ============ 替换为支持中文的显示逻辑 ============
            test_image = put_chinese_text(test_image, "测试图像", (100, 200), text_size=40)
            # ==================================================

            # 保存测试图像
            saved_path = save_frame_with_timestamp(test_image, "test_image")

            if saved_path and os.path.exists(saved_path):
                print(f"测试成功！文件已创建: {saved_path}")
                print(f"文件大小: {os.path.getsize(saved_path)} 字节")

                # 显示测试图像
                cv2.imshow("测试图像", test_image)
                cv2.waitKey(2000)
                cv2.destroyAllWindows()
            else:
                print("测试失败！")

        elif choice == "6":
            print("退出程序...")

        elif choice == "5":
            powermeter = connect_power_meter(0)
            if powermeter is None:
                print("未能连接功率计，划线将不记录功率")

            try:
                f=20
                for f in range(20,140,3):
                    power_samples = []
                    avg_power = None
                    # 获取当前XY位置作为划线起点
                    error_code, xy_response = get_stage_position()
                    if error_code == 0:
                        x_current, y_current = map(float, xy_response.split(','))
                    else:
                        x_current, y_current = 0.0, 0.0
                        print("获取XY位置失败，使用默认值(0,0)")

                    # 定义划线参数
                    line_length = 500.0  # 划线长度（微米）
                    x_feedrate = f  # 进给速度（微米/秒）
                    y_feedrate = 100.0

                    # 打开激光器
                    print("打开激光器...")
                    send_shutter_command('open')

                    # 开始划线循环
                    print("开始划线...")
                    print("方案1: 划一条直线")
                    x_target = x_current - line_length
                    move_stage_speed(x_feedrate, 0)
                    start_time = time.time()

                    # 实时测功率，直到载物台空闲或超时
                    while True:
                        if powermeter is not None:
                            power_value = measure_power(powermeter)
                            if power_value is not None:
                                power_samples.append(power_value)

                        error_code, response = cmd("controller.stage.busy.get", verbose=False)
                        if error_code == 0 and response.strip() == "0":
                            break

                        if time.time() - start_time > line_length / x_feedrate + 5.0:
                            print("等待划线完成超时，强制退出测量循环")
                            break

                        time.sleep(0.1)

                    move_stage_speed(0, 0)
                    send_shutter_command('close')

                    if power_samples:
                        avg_power = sum(power_samples) / len(power_samples)
                        print(f"本次划线平均功率: {avg_power:.4f} W")
                    else:
                        print("未获取到功率数据")

                    # 自动截图功能 - 添加在这里
                    print("激光烧蚀完成，开始自动截图...")

                    time.sleep(2)
                    camera_index=0
                    try:
                        # 使用AutoFocusWithDisplay类拍照
                        af = AutoFocusWithDisplay(camera_index)
                        af.display_enabled = True
                        af.save_images = False

                        if af.open_camera():
                            # 等待相机稳定
                            time.sleep(0.5)

                            # 捕获图像，显示2秒钟
                            mat, sharpness = af.capture_with_display(z_position=0, delay_ms=2000)
                            if mat is not None:
                                # 保存图像，文件名包含位置信息
                                error_code, xy_final = get_stage_position()
                                if error_code == 0:
                                    x_final, y_final = map(float, xy_final.split(','))
                                else:
                                    x_final, y_final = 0.0, 0.0
                                    print("获取XY位置失败，使用默认值(0,0)")
                                filename_parts = [f"laser_line_X{x_feedrate:.0f}_Y{y_final:.0f}"]
                                if avg_power is not None:
                                    filename_parts.append(f"P{avg_power:.4f}W")
                                filename = "_".join(filename_parts)
                                saved_path = save_frame_with_timestamp(mat, filename)
                                if saved_path:
                                    print(f"照片已保存: {saved_path}")

                                # 显示图像
                                cv2.imshow("激光划线结果", mat)
                                cv2.waitKey(3000)
                                cv2.destroyAllWindows()
                            af.close()
                        else:
                            print("无法打开相机拍照")
                    except Exception as e:
                        print(f"拍照过程中出错: {e}")
                        import traceback

                        traceback.print_exc()

                    print("\n激光划线任务完成！")

            finally:
                if powermeter is not None:
                    close_power_meter(powermeter)

        else:
            print("无效选项")

        # 7. 断开连接
        print("\n7. 断开移动平台连接...")
        disconnect_controller()

    except KeyboardInterrupt:
        print("\n\n用户中断程序")
    except Exception as e:
        print(f"\n程序执行出错: {e}")
        import traceback

        traceback.print_exc()
    finally:
        # 清理资源
        cv2.destroyAllWindows()
        print("\n程序结束")

    # 上面由于收集原始数据集
    # picturedeal+model
    # 现在开始每拍一张照就实时加入数据集，同时对参数进行调整（xy轴速度，z轴高度等）