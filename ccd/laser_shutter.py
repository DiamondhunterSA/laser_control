import serial
import time

ser = None

# 定义核心命令函数
# 全局命令（十进制数）
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

def init_shutter(port='COM4', baudrate=9600, timeout=1):
    global ser
    try:
        if ser is not None and ser.is_open:
            return True

        ser = serial.Serial(
            port=port,
            baudrate=baudrate,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=timeout,
        )
        print(f"已连接到 {ser.port}")
        return True
    except Exception as e:
        print(f"初始化快门串口失败: {e}")
        ser = None
        return False


# 发送命令的函数
def send_shutter_command(command_name):
    if ser is None or not ser.is_open:
        print("快门串口未初始化")
        return False

    if command_name in GLOBAL_COMMANDS:
        cmd_byte = GLOBAL_COMMANDS[command_name].to_bytes(1, 'big')
        ser.write(cmd_byte)
        print(f"已发送命令: {command_name} (字节: {cmd_byte.hex()})")
        return True

    print(f"未知命令: {command_name}")
    return False


def close_shutter():
    global ser
    if ser is not None and ser.is_open:
        ser.close()
        print("串口已关闭")
    ser = None


if __name__ == '__main__':
    try:
        if init_shutter():
            #send_shutter_command('open')
            #time.sleep(2)
            send_shutter_command('close')
    except Exception as e:
        print(f"操作出错: {e}")
    finally:
        close_shutter()


