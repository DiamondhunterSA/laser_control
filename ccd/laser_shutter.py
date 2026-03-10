import serial
import time

# 配置串口参数 (端口号请根据你的实际情况修改)
ser = serial.Serial(
    port='COM4',        # 串口号
    baudrate=9600,      # 波特率
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1           # 读超时时间（秒）
)

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

# 发送命令的函数
def send_shutter_command(command_name):
    if command_name in GLOBAL_COMMANDS:
        cmd_byte = GLOBAL_COMMANDS[command_name].to_bytes(1, 'big')
        ser.write(cmd_byte)
        print(f"已发送命令: {command_name} (字节: {cmd_byte.hex()})")
    else:
        print(f"未知命令: {command_name}")

# 使用示例
try:
    if ser.is_open:
        print(f"已连接到 {ser.port}")

        # 示例：打开快门，等待2秒，然后关闭
        send_shutter_command('open')
        time.sleep(20)
        #send_shutter_command('close')

        # 示例：发送一个触发脉冲
        # send_shutter_command('trigger')
        # time.sleep(0.5) # 根据快门动作时间调整
        # send_shutter_command('trigger') # 再次触发以关闭（取决于当前状态）

except Exception as e:
    print(f"操作出错: {e}")
finally:
    ser.close()
    print("串口已关闭")


