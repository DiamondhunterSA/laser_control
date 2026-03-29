import os
import time
from ctypes import WinDLL, create_string_buffer

SDKPrior = None
sessionID = None
rx = create_string_buffer(1000)
_last_stage_velocity = (None, None)


def load_stage_sdk(sdk_dir=r"D:\\ccd\\PriorSDK 2.0.0\\x64"):
    global SDKPrior

    if SDKPrior is not None:
        return True

    dll_path = os.path.join(sdk_dir, "PriorScientificSDK.dll")

    if sdk_dir not in os.environ.get("PATH", ""):
        os.environ["PATH"] = sdk_dir + os.pathsep + os.environ.get("PATH", "")

    if not os.path.exists(dll_path):
        print(f"错误: DLL文件不存在: {dll_path}")
        return False

    try:
        SDKPrior = WinDLL(dll_path)
        print("DLL加载成功")
        return True
    except Exception as e:
        print(f"DLL加载失败: {e}")
        return False


def init_sdk():
    global sessionID

    if not load_stage_sdk():
        return False

    ret = SDKPrior.PriorScientificSDK_Initialise()
    if ret:
        print(f"初始化失败: {ret}")
        return False

    ret = SDKPrior.PriorScientificSDK_Version(rx)
    if ret == 0:
        print(f"DLL版本: {rx.value.decode()}")

    sessionID = SDKPrior.PriorScientificSDK_OpenNewSession()
    if sessionID < 0:
        print(f"获取sessionID失败: {sessionID}")
        return False

    print(f"SessionID = {sessionID}")
    return True


def cmd(msg, verbose=True):
    if SDKPrior is None or sessionID is None:
        return -1, "SDK未初始化"

    if verbose:
        print(f"发送命令: {msg}")

    ret = SDKPrior.PriorScientificSDK_cmd(
        sessionID,
        create_string_buffer(msg.encode()),
        rx,
    )

    response = rx.value.decode()

    if verbose:
        if ret:
            print(f"API错误 {ret}: {response}")
        else:
            print(f"命令成功: {response}")

    return ret, response


def connect_to_controller(port):
    return cmd(f"controller.connect {port}")


def disconnect_controller():
    return cmd("controller.disconnect")


def get_stage_position():
    return cmd("controller.stage.position.get")


def get_stage_zposition():
    return cmd("controller.z.position.get")


def move_stage_absolute(x, y):
    return cmd(f"controller.stage.goto-position {x} {y}")


def set_stage_speed(speed_x, speed_y):
    return cmd(f"controller.stage.speed.set {float(speed_x)} {float(speed_y)}")


def move_stage_zabsolute(z):
    return cmd(f"controller.z.goto-position {z}")


def move_stage_speed(speed_x, speed_y):
    return move_stage_velocity(speed_x, speed_y)


def move_stage_relative(delta_x, delta_y):
    return cmd(f"controller.stage.move-relative {delta_x} {delta_y}")


def move_stage_velocity(speed_x, speed_y, dedupe=True, verbose=False):
    global _last_stage_velocity

    vx = float(speed_x)
    vy = float(speed_y)

    if dedupe and _last_stage_velocity == (vx, vy):
        return 0, "velocity unchanged"

    ret, response = cmd(f"controller.stage.move-at-velocity {vx} {vy}", verbose=verbose)
    if ret == 0:
        _last_stage_velocity = (vx, vy)
    return ret, response


def stop_stage_xy(verbose=False):
    return move_stage_velocity(0.0, 0.0, dedupe=True, verbose=verbose)


def reset_stage_velocity_cache():
    global _last_stage_velocity
    _last_stage_velocity = (None, None)


def wait_stage_idle(timeout=10.0):
    start_time = time.time()
    while time.time() - start_time < timeout:
        error_code, response = cmd("controller.stage.busy.get", verbose=False)
        if error_code == 0 and response.strip() == "0":
            return True
        time.sleep(0.1)
    print("等待载物台空闲超时！")
    return False


def wait_z_idle(timeout=10.0):
    start_time = time.time()
    while time.time() - start_time < timeout:
        error_code, response = cmd("controller.z.busy.get", verbose=False)
        if error_code == 0 and response.strip() == "0":
            return True
        time.sleep(0.1)
    print("等待Z轴空闲超时！")
    return False
