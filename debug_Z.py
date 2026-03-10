import time
import os
from ctypes import WinDLL, create_string_buffer

# ==================== 配置区域 ====================
SDK_DIR = r"D:\ccd\PriorSDK 2.0.0\x64"
DLL_PATH = os.path.join(SDK_DIR, "PriorScientificSDK.dll")
PORT = 3  # 根据你主代码中的设置
# =================================================

# 环境初始化
if SDK_DIR not in os.environ['PATH']:
    os.environ['PATH'] = SDK_DIR + os.pathsep + os.environ['PATH']

try:
    SDKPrior = WinDLL(DLL_PATH)
    rx = create_string_buffer(1000)
    print("✅ SDK 加载成功")
except Exception as e:
    print(f"❌ SDK 加载失败: {e}")
    exit()

def send_cmd(session, command):
    """发送命令并返回响应"""
    ret = SDKPrior.PriorScientificSDK_cmd(session, create_string_buffer(command.encode()), rx)
    resp = rx.value.decode().strip()
    return ret, resp

def wait_z_idle(session, timeout=15):
    """循环查询 Z 轴是否停止移动"""
    start = time.time()
    while time.time() - start < timeout:
        ret, resp = send_cmd(session, "controller.z.busy.get")
        if ret == 0 and resp == "0":
            return True
        time.sleep(0.1)
    return False

def debug_z_axis():
    # 1. 初始化
    SDKPrior.PriorScientificSDK_Initialise()
    sessionID = SDKPrior.PriorScientificSDK_OpenNewSession()
    if sessionID < 0:
        print("❌ 无法开启 Session")
        return

    # 2. 连接
    ret, resp = send_cmd(sessionID, f"controller.connect {PORT}")
    if ret != 0:
        print(f"❌ 连接失败: {resp}")
        return
    print(f"✅ 已连接控制器 (Port {PORT})")

    try:
        # 3. 获取初始位置
        _, start_pos = send_cmd(sessionID, "controller.z.position.get")
        print(f"📍 当前 Z 轴位置: {start_pos}")

        print("\n--- 开始调试移动 ---")
        test_offset = 100  # 移动位移量
        
        # 4. 测试绝对移动 (向上)
        target_up = int(start_pos) + test_offset
        print(f"🚀 尝试移动到绝对位置: {target_up}...")
        send_cmd(sessionID, f"controller.z.goto/-position {target_up}")
        
        if wait_z_idle(sessionID):
            _, final_pos = send_cmd(sessionID, "controller.z.position.get")
            print(f"🏁 到达位置: {final_pos}")
        else:
            print("⚠️ 移动超时，Z 轴可能未动作或 busy 状态异常")

        # 5. 测试回到原点
        print(f"⏪ 正在返回初始位置: {start_pos}...")
        send_cmd(sessionID, f"controller.z.goto-position {start_pos}")
        wait_z_idle(sessionID)
        
        _, final_pos = send_cmd(sessionID, "controller.z.position.get")
        print(f"🏁 最终位置: {final_pos}")

    finally:
        send_cmd(sessionID, "controller.disconnect")
        print("\n🔌 已断开连接")

if __name__ == "__main__":
    debug_z_axis()