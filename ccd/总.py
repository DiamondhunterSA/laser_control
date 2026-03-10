import sys
import os
import numpy as np
import cv2
import time
from duijiao import calculate_sharpness
from laser_shutter import send_shutter_command

# 功率计加载
"""from pyThorlabsPM100x.driver import ThorlabsPM100x
powermeter = ThorlabsPM100x()
available_devices = powermeter.list_devices()
print(available_devices)
powermeter.connect_device(device_addr = available_devices[0][0])
print(powermeter.power)
powermeter.disconnect_device()"""

# ccd加载
print(f"Python版本: {sys.version}")
correct_sdk_path = r"E:\ccd\DVP2 SDK\Sample\Python\lib\windows\python3.6\x64"
if correct_sdk_path not in sys.path:
    sys.path.insert(0, correct_sdk_path)
current_system_path = os.environ.get('PATH', '')
if correct_sdk_path not in current_system_path:
    os.environ['PATH'] = correct_sdk_path + os.pathsep + current_system_path
print(f"[配置信息] 模块搜索路径已添加: {correct_sdk_path}")
print(f"[配置信息] 系统DLL路径已添加: {correct_sdk_path}")

from dvp import *

# ccd函数:frame2mat(frameBuffer),setCameraParams(camera),runccd()
# 将帧信息转换为numpy的矩阵对象，后续可以通过opencv的cvtColor转换为特定的图像格式
def frame2mat(frameBuffer):
    frame, buffer = frameBuffer
    bits = np.uint8 if (frame.bits == Bits.BITS_8) else np.uint16
    shape = None
    convertType = None
    if (frame.format >= ImageFormat.FORMAT_MONO and frame.format <= ImageFormat.FORMAT_BAYER_RG):
        shape = 1
    elif (frame.format == ImageFormat.FORMAT_BGR24 or frame.format == ImageFormat.FORMAT_RGB24):
        shape = 3
    elif (frame.format == ImageFormat.FORMAT_BGR32 or frame.format == ImageFormat.FORMAT_RGB32):
        shape = 4
    else:
        return None
    mat = np.frombuffer(buffer, bits)
    mat = mat.reshape(frame.iHeight, frame.iWidth, shape)  # 转换维度
    return mat

# 这个函数演示相机功能的基本调用方法，仅供参考
def setCameraParams(camera):
    # 以下设置ROI
    roiDescr = camera.RoiDescr  # ROI的描述
    roi = camera.Roi  # 获取ROI
    roi.X = 0  # 横纵坐标
    roi.Y = 0
    roi.W = 400  # 宽度，高度
    roi.H = 400
    camera.Roi = roi  # 设置ROI

    camera.ResolutionModeSel = 0
    print("分辨率模式0")

    light=135
    camera.AeOperation = AeOperation.AE_OP_CONTINUOUS  # 启动自动曝光
    camera.AntiFlick = AntiFlick.ANTIFLICK_DISABLE  # 直流光源
    camera.Contrast = 199 # 设置对比度
    camera.AeTarget = light  # 设置需要调节到的目标亮度
    camera.AeMode = AeMode.AE_MODE_AE_ONLY  # 仅仅自动调节曝光时间
    camera.AwbOperation = AwbOperation.AWB_OP_CONTINUOUS # 启动白平衡
    # 设置RGB增益（彩色相机可设置）
    # camera.GGain = 1
    # camera.RGain = 1
    # camera.BGain = 1
    camera.SaveConfig("example.ini")

# 定义主函数
def runccd():
    cameraInfo = Refresh();  # 刷新并获取相机列表
    if (len(cameraInfo) == 0):  # 没有任何设备则退出
        print(u"没有找到设备")
        return

    for k, v in enumerate(cameraInfo):  # 打印相机索引和名称
        print(k, "->", v.FriendlyName)

    while (True):  # 循环直到打开一台相机
        try:
            str = input("请选定将要打开的相机索引号(0,1,2...):")
            index = (int)(str)  # 输入的索引号字符串转换为整数
            camera = Camera(index)  # 以索引号的方式打开相机
            # camera = Camera(cameraInfo[index].FriendlyName)#或以名称的方式打开相机
            break
        except dvpException as e:
            print(u"打开相机失败:", e.Status)  # 如果是DVP的标准异常
        except BaseException as e:
            print(u"非法的索引号:", str)  # 其他异常

    try:
        camera.TriggerState = False  # 从触发模式切换到连续出图模式
        setCameraParams(camera)  # 设置其他的相机的参数
        camera.Start()  # 启动视频流
    except dvpException as e:
        print(u"操作相机出错:", e.Status)

    while (cv2.waitKey(1) != 27):  # 按ESC键则退出循环
        try:
            print(camera.FrameCount)  # 打印帧统计信息
            frame = camera.GetFrame(4000)  # 从相机采集图像数据，超时时间为4000毫秒
        except dvpException as e:
            print(u"采集图像数据失败:", e.Status)
            if (e.Status == Status.DVP_STATUS_TIME_OUT):
                continue  # 如果只是超时错误，则继续采集
            break  # 其他错误则中止采集

        mat = frame2mat(frame)  # 转换为标准数据格式
        cv2.imshow(u"Preview (Press ESC exit)", mat)  # 显示图像数据

    cv2.destroyAllWindows()  # 销毁窗口
    camera.Stop()  # 停止视频流
    camera.Close()  # 关闭相机
    return camera

# 截图功能
def save_frame_with_timestamp(mat, prefix="screenshot", save_dir=None):
    import time
    import os

    if save_dir is None:
        # 默认保存到当前目录的"screenshots"子文件夹
        save_dir = os.path.join(os.getcwd(), "screenshots")

    # 确保目录存在
    if not os.path.exists(save_dir):
        os.makedirs(save_dir)

    timestamp = time.strftime("%Y%m%d_%H%M%S")
    filename = f"{prefix}_{timestamp}.png"
    full_path = os.path.join(save_dir, filename)

    cv2.imwrite(full_path, mat)
    print(f"图像已保存到: {full_path}")
    return full_path

# 移动平台部分
# 移动平台加载
from ctypes import WinDLL, create_string_buffer
sdk_dir = r"E:\ccd\PriorSDK 2.0.0\x64"
dll_path = os.path.join(sdk_dir, "PriorScientificSDK.dll")
# 将 SDK 目录添加到系统 PATH，以便加载依赖的 DLL
if sdk_dir not in os.environ['PATH']:
    os.environ['PATH'] = sdk_dir + os.pathsep + os.environ['PATH']
print(f"SDK 目录: {sdk_dir}")
print(f"DLL 路径: {dll_path}")

# 检查 DLL 是否存在
if not os.path.exists(dll_path):
    print(f"错误: DLL 文件不存在: {dll_path}")
    print("当前目录内容:")
    for f in os.listdir('.'):
        print(f"  {f}")
    raise RuntimeError("DLL could not be loaded.")
try:
    # 加载 DLL
    SDKPrior = WinDLL(dll_path)
    print("✅ DLL 加载成功!")
except Exception as e:
    print(f"❌ DLL 加载失败: {e}")
    print("可能的原因:")
    print("1. DLL 文件损坏")
    print("2. 缺少依赖的 DLL（如 VC++ Redistributable）")
    print("3. 位数不匹配（32位 vs 64位）")
    raise
# 字节数，防止溢出？
rx = create_string_buffer(1000)
# 是否在实际使用，true为实际使用
realhw = False
# 调试dll与通信是否正常
def cmd(msg):
    print(msg)
    ret = SDKPrior.PriorScientificSDK_cmd(
        sessionID, create_string_buffer(msg.encode()), rx
    )
    # 以下输出实际使用可以注释
    if ret:
        print(f"Api error {ret}")
    else:
        print(f"OK {rx.value.decode()}")
    input("Press ENTER to continue...")
    # 关键返回值，不可注释
    return ret, rx.value.decode()

# 初始化
ret = SDKPrior.PriorScientificSDK_Initialise()
if ret:
    print(f"Error initialising {ret}")
    sys.exit()
else:
    print(f"Ok initialising {ret}")
# 初始化
ret = SDKPrior.PriorScientificSDK_Version(rx)
print(f"dll version api ret={ret}, version={rx.value.decode()}")
# 初始化
sessionID = SDKPrior.PriorScientificSDK_OpenNewSession()
if sessionID < 0:
    print(f"Error getting sessionID {ret}")
else:
    print(f"SessionID = {sessionID}")
# 初始化
ret = SDKPrior.PriorScientificSDK_cmd(
    sessionID, create_string_buffer(b"dll.apitest 33 goodresponse"), rx
)
print(f"api response {ret}, rx = {rx.value.decode()}")
input("Press ENTER to continue...")
# 初始化
ret = SDKPrior.PriorScientificSDK_cmd(
    sessionID, create_string_buffer(b"dll.apitest -300 stillgoodresponse"), rx
)
print(f"api response {ret}, rx = {rx.value.decode()}")
input("Press ENTER to continue...")

# 真实场景使用示例
if realhw:
    print("Connecting...")
    # substitute 3 with your com port Id
    cmd("controller.connect 3")

    # test an illegal command
    cmd("controller.stage.position.getx")

    # get current XY position in default units of microns
    cmd("controller.stage.position.get")
    """# 示例：发送命令并获取原始返回结果
    error_code, response_string = cmd("controller.stage.position.get")
    if error_code == 0:
        # 成功，处理 response_string (如 "1234,5678")
        x, y = map(int, response_string.split(','))
    else:
        # 失败，error_code是API错误码，response_string可能有详细信息
        print(f"Command failed with code: {error_code}")"""

    # re-define this current position as 1234,5678
    cmd("controller.stage.position.set 1234 5678")

    # check it worked
    cmd("controller.stage.position.get")

    # set it back to 0,0
    cmd("controller.stage.position.set 0 0")
    cmd("controller.stage.position.get")

    # start a move to a new position, normally you would poll
    # 'controller.stage.busy.get' until response = 0
    cmd("controller.stage.goto-position 1234 5678")

    # example velocity move of 10u/s in both x and y
    cmd("controller.stage.move-at-velocity 10 10")

    # see busy status
    cmd("controller.stage.busy.get")

    # stop velocity move
    cmd("controller.stage.move-at-velocity 0 0")

    # see busy status */
    cmd("controller.stage.busy.get")

    # see new position
    cmd("controller.stage.position.get")

    # disconnect cleanly from controller
    cmd("controller.disconnect")

else:
    input("Press ENTER to continue...")

# 连接控制器，port代表接口
def connect_to_controller(port):
    return cmd(f"controller.connect {port}")

# 获取载物台当前x，y位置
def get_stage_position():
    return cmd("controller.stage.position.get")

# 获取载物台当前z位置
def get_stage_zposition():
    return cmd("controller.z.position.get")

# 移动载物台到绝对坐标x，y (单位: 微米)
def move_stage_absolute(x, y):
    return cmd(f"controller.stage.goto-position {x} {y}")

# 移动载物台到z值
def move_stage_zabsolute(z):
    return cmd(f"controller.z.goto-position {z}")

def move_stage_speed(speed_x,speed_y):
    cmd("controller.stage.move-at-velocity {speed_x} {speed_y}")
    

# 等待载物台停止移动
def wait_stage_idle(timeout=10.0):
    import time
    start_time = time.time()
    while time.time() - start_time < timeout:
        error_code, response = cmd("controller.stage.busy.get")
        if error_code == 0 and response == "0":  # 0 表示空闲
            return True
        time.sleep(0.1) # 避免频繁查询
    print("等待载物台空闲超时！")
    return False






# 主函数
if __name__ == "__main__":
    connect_to_controller(8)
    z = get_stage_zposition()
    camera=runccd()
    frame = camera.GetFrame(4000)
    mat = frame2mat(frame)
    image = save_frame_with_timestamp(mat, "ccd_capture")
    sharpness=calculate_sharpness(image)
    deviate=1
    #寻找最佳成像
    while deviate>0.01:
        z=z-deviate
        move_stage_zabsolute(z)
        image = save_frame_with_timestamp(mat, "ccd_capture")
        sharpness2 = calculate_sharpness(image)
        if sharpness2 < sharpness:
            z = z + deviate
            deviate=deviate/10
    #开始划线
    send_shutter_command('open')
    time.sleep(20)



      # 获取当前XY位置作为划线起点
    error_code, xy_response = get_stage_position()
    if error_code == 0:
            x_current, y_current = map(float, xy_response.split(','))
    else:
        x_current, y_current = 0.0, 0.0
        print("获取XY位置失败，使用默认值(0,0)")
    
    # 定义划线参数
    line_length = 1000.0  # 划线长度（微米）
    x_feedrate = 100.0     # 进给速度（微米/秒）
    y_feedrate = 100.0
    
    # 打开激光器
    print("打开激光器...")
    send_shutter_command('open')
    
    # 开始划线循环
    print("开始划线...")
    
    # 方案1: 划一条直线
    '''print("方案1: 划一条直线")
    x_target = x_current + line_length
    move_stage_speed(x_feedrate, 0)
    move_stage_absolute(x_target, y_current)
    wait_stage_idle(line_length / x_feedrate + 2.0)  # 等待移动完成'''
    
    # 方案2: 划一个矩形
    '''
    print("方案2: 划一个矩形")
    rectangle_width = 500.0
    rectangle_height = 300.0
   
  
    # 划矩形的四个边
    points = [
        (x_current + rectangle_width, y_current),  # 右上角
        (x_current + rectangle_width, y_current + rectangle_height),  # 右下角
        (x_current, y_current + rectangle_height),  # 左下角
        (x_current, y_current)  # 回到起点
    ]
    
    for i, (x_target, y_target) in enumerate(points):
        print(f"移动到点{i+1}: ({x_target}, {y_target})")
        move_stage_absolute(x_target, y_target)
        # 计算移动时间（距离/速度）
        if i == 0:
            distance = rectangle_width
            wait_stage_idle(distance / x_feedrate + 1.0)
        elif i == 1:
            distance = rectangle_height
            wait_stage_idle(distance / y_feedrate + 1.0)
        elif i == 2:
            distance = rectangle_width
            wait_stage_idle(distance / x_feedrate + 1.0)
        else:
            distance = rectangle_height
            wait_stage_idle(distance / y_feedrate + 1.0)'''
        
       
    
    # 方案3: 划线阵列（多条平行线）
    print("方案3: 划线阵列")
    num_lines = 5
    spacing = 50.0  # 线间距
    
    for i in range(num_lines):
        # 计算每条线的Y位置
        y_line = y_current + i * spacing


        # 关闭激光器
        print("关闭激光器...")
        send_shutter_command('close')
        # 移动到线起点
        move_stage_absolute(x_current, y_line)
        send_shutter_command('open')
        wait_stage_idle(1.0)
        
        # 划线
        x_target = x_current + line_length
        move_stage_speed(x_feedrate, 0)
        move_stage_absolute(x_target, y_line)
        wait_stage_idle(line_length / feed_rate + 1.0)
        
        print(f"完成第{i+1}条线")
    
 
    # 关闭激光器
    print("关闭激光器...")
    send_shutter_command('close')
    
    # 回到起始点
    print("返回起始点...")
    move_stage_absolute(x_current, y_current)
    wait_stage_idle(2.0)
    
    print("划线完成！")



