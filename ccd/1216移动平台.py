from ctypes import WinDLL, create_string_buffer
import os
import sys

# 设置 DLL 搜索路径
sdk_dir = r"E:\ccd\PriorSDK 2.0.0\x64"  # 修改为你的实际路径
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
    cmd("controller.connect 8")

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

# 获取载物台当前位置
def get_stage_position():
    return cmd("controller.stage.position.get")

# 移动载物台到绝对坐标 (单位: 微米)
def move_stage_absolute(x, y):
    return cmd(f"controller.stage.goto-position {x} {y}")

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

if __name__ == "__main__":
    connect_to_controller(8)
    get_stage_position()
    move_stage_absolute(17093,11291)
    get_stage_position()
    """if wait_stage_idle():
       print("移动完成，当前位置：", get_stage_position())"""