import sys
import os

print(f"Python版本: {sys.version}")
# ccd路径
correct_sdk_path = r"E:\ccd\DVP2 SDK\Sample\Python\lib\windows\python3.6\x64"
if correct_sdk_path not in sys.path:
    sys.path.insert(0, correct_sdk_path)
current_system_path = os.environ.get('PATH', '')
if correct_sdk_path not in current_system_path:
    os.environ['PATH'] = correct_sdk_path + os.pathsep + current_system_path
print(f"[配置信息] 模块搜索路径已添加: {correct_sdk_path}")
print(f"[配置信息] 系统DLL路径已添加: {correct_sdk_path}")
from dvp import *
import numpy as np
import cv2

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



if __name__ == '__main__':
    kuaimen=1
    while kuaimen==1:
       runccd()
       #跳转到移动平台

