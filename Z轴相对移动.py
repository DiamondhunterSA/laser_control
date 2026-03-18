import ctypes
import time
import sys
import os

class PriorZStage:
    def __init__(self, dll_path, port, resolution_microns=0.1):
        """
        初始化控制器
        :param dll_path: SDK DLL 的文件路径
        :param port: COM 端口号 (整数，例如 4 代表 COM4)
        :param resolution_microns: SDK 默认的分辨率，通常为 0.1 微米 (100nm)
        """
        self.port = port
        self.resolution = resolution_microns
        self.session_id = -1
        
        # 简单检查 DLL 文件是否存在
        if not os.path.exists(dll_path):
            print(f"错误: 找不到 DLL 文件: {dll_path}")
            sys.exit(1)

        try:
            # 1. 加载 DLL
            # 注意：如果 Python 是 64 位，必须使用 64 位的 DLL；32 位同理
            self.sdk = ctypes.CDLL(dll_path)
            
            # 2. SDK 初始化
            if self.sdk.PriorScientificSDK_Initialise() != 0:
                raise Exception("SDK 初始化失败")
            
            # 3. 创建会话
            self.session_id = self.sdk.PriorScientificSDK_OpenNewSession()
            if self.session_id < 0:
                raise Exception("创建会话失败")
            
            # 4. 连接控制器
            # controller.connect <port>
            print(f"正在连接端口 COM{port} ...")
            connect_res = self._send_cmd(f"controller.connect {port}")
            if connect_res != "0":
                 raise Exception(f"连接失败，控制器返回: {connect_res}")
            
            # 5. 执行硬件自检，确认步长设置
            self._check_resolution_settings()
            
        except Exception as e:
            print(f"初始化错误: {e}")
            self.close()
            sys.exit(1)

    def _send_cmd(self, cmd_str):
        """
        发送命令的底层封装
        """
        # 创建 512 字节的缓存区用于接收结果
        response_buffer = ctypes.create_string_buffer(512)
        cmd_bytes = cmd_str.encode('ascii')
        
        # 调用 DLL 函数
        ret = self.sdk.PriorScientificSDK_cmd(self.session_id, cmd_bytes, response_buffer)
        
        if ret != 0:
            raise Exception(f"指令 '{cmd_str}' SDK调用失败，错误码: {ret}")
        
        return response_buffer.value.decode('ascii').strip()

    def _check_resolution_settings(self):
        """
        检查 Z 轴步长设置
        """
        try:
            # 获取 Z 轴微步设置 (通常是 50)
            ss_val = self._send_cmd("controller.z.ss.get")
            # 获取每转微米数 (通常是 100)
            upr_val = self._send_cmd("controller.z.microns-per-rev.get")
            
            print(f"--- 硬件自检 ---")
            print(f"Z轴 SS (Step Size): {ss_val}")
            print(f"Z轴 每转微米数: {upr_val}")
            
            # 简单验证逻辑
            if ss_val == "50" and upr_val == "100":
                 print("硬件配置符合标准 (0.1 微米/步)")
            else:
                 print(f"注意: 硬件配置可能非标准，当前代码设定的分辨率为 {self.resolution} 微米")
            print("----------------")
        except Exception as e:
            print(f"自检警告: 无法读取硬件设置 ({e})")

    def is_busy(self):
        """
        查询 Z 轴是否忙碌
        返回值: True (忙碌), False (空闲)
        """
        # SDK 文档: "0" idle, "4" Z moving
        return self._send_cmd("controller.z.busy.get") != "0"

    def move_rel_microns(self, microns):
        """
        Z 轴相对移动指定微米数
        :param microns: 移动距离 (浮点数)，例如 2.0
        """
        # 计算步数： 2.0 / 0.1 = 20 步
        steps = int(microns / self.resolution)
        
        if steps == 0:
            print("移动距离过小，忽略。")
            return

        print(f"请求移动: {microns} 微米 (计算步数: {steps})")
        
        # 发送相对移动指令 
        self._send_cmd(f"controller.z.move-relative {steps}")
        
        # 忙碌等待
        while self.is_busy():
            time.sleep(0.05) # 50ms 轮询一次
        
        print(f"移动完成。")

    def get_position(self):
        """
        获取当前 Z 轴位置并转换为微米
        """
        # 获取位置 [cite: 327]
        pos_str = self._send_cmd("controller.z.position.get")
        try:
            pos_units = int(pos_str)
            pos_microns = pos_units * self.resolution
            return pos_microns
        except ValueError:
            return 0.0

    def close(self):
        """
        断开连接并释放会话
        """
        if self.session_id >= 0:
            try:
                self._send_cmd("controller.disconnect") # [cite: 123]
                self.sdk.PriorScientificSDK_CloseSession(self.session_id)
                print("连接已安全断开。")
            except:
                pass
            self.session_id = -1


def move_rel_microns_with_cmd(cmd_func, microns, resolution_microns=0.1, poll_interval=0.05):
    """
    使用外部 cmd 函数执行 Z 轴相对移动。
    cmd_func 需要兼容: cmd_func(message, verbose=False) -> (error_code, response)
    """
    steps = int(microns / resolution_microns)
    if steps == 0:
        print("移动距离过小，忽略。")
        return False

    error_code, response = cmd_func(f"controller.z.move-relative {steps}", verbose=False)
    if error_code != 0:
        print(f"Z轴相对移动失败: {response}")
        return False

    while True:
        busy_code, busy_response = cmd_func("controller.z.busy.get", verbose=False)
        if busy_code == 0 and busy_response.strip() == "0":
            break
        time.sleep(poll_interval)

    return True


def get_z_position_microns_with_cmd(cmd_func, resolution_microns=0.1):
    """
    使用外部 cmd 函数读取当前 Z 轴位置（微米）。
    """
    error_code, response = cmd_func("controller.z.position.get", verbose=False)
    if error_code != 0:
        return None

    try:
        return int(response.strip()) * resolution_microns
    except Exception:
        return None

# ==========================================
# 主程序
# ==========================================

if __name__ == "__main__":
    # --- 配置区域 ---
    # 请修改为您电脑上 DLL 的实际路径
    # 例如: r"C:\Program Files\Prior Scientific\Prior SDK\PriorScientificSDK.dll"
    DLL_PATH = r"D:\ccd\PriorSDK 2.0.0\x64\PriorScientificSDK.dll" 
    
    # 【已修改】端口号设置为 4
    COM_PORT = 3
    
    # ----------------
    
    z_stage = PriorZStage(DLL_PATH, COM_PORT)
    
    try:
        # 1. 获取初始位置
        start_z = z_stage.get_position()
        print(f"初始位置: {start_z:.2f} 微米")
        
        # 2. 向上移动 2 微米  <--- 修改这里的数字！！！！！
        z_stage.move_rel_microns(2.0)
        
        # 3. 验证新位置
        end_z = z_stage.get_position()
        print(f"结束位置: {end_z:.2f} 微米")
        print(f"实际位移: {end_z - start_z:.2f} 微米")
        
    except KeyboardInterrupt:
        print("\n用户中断操作")
    finally:
        z_stage.close()