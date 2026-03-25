"""
K10CR1_serial.py
控制 Thorlabs K10CR1 旋转安装座，通过串口（COM）发送绝对移动命令。
使用时需要将串口设备的VCP（虚拟接口）打开才能找到COM号。
"""

import serial
import time

# K10CR1 转换常数
# 位置：1度 = 136533 微步
# 速度：1度/秒 = 7329109 微步/秒
# 加速度：1度/秒² = 1502 微步/秒²
STEP_PER_DEG = 136533
VEL_FACTOR = 7329109      # 对应 1 deg/s 的速度值
ACC_FACTOR = 1502         # 对应 1 deg/s² 的加速度值

def build_move_absolute(angle_deg, channel=0x01):
    """
    构造 MGMSG_MOT_MOVE_ABSOLUTE (0x0453) 命令字节流。
    angle_deg: 目标角度（度）
    channel: 通道标识，K10CR1为单通道，默认0x01
    返回：完整的字节数组（包含6字节头 + 6字节数据）
    """
    # 计算微步数
    position = int(angle_deg * STEP_PER_DEG)
    # 数据包：通道标识(2字节) + 绝对位置(4字节，小端序)
    data = bytearray()
    data += channel.to_bytes(2, 'little')        # 通道标识
    data += position.to_bytes(4, 'little')       # 绝对位置（微步）
    # 消息头：ID(0x0453) + 数据长度(0x0006) + 目的地址(0x50|0x80) + 源地址(0x01)
    header = bytearray([0x53, 0x04, 0x06, 0x00, 0xD0, 0x01])
    return header + data

def build_set_velparams(max_vel_degps, acc_degps2, min_vel=0, channel=0x01):
    """
    构造 MGMSG_MOT_SET_VELPARAMS (0x0413) 命令字节流。
    max_vel_degps: 最大速度（度/秒）
    acc_degps2: 加速度（度/秒²）
    min_vel: 最小速度（通常为0）
    channel: 通道标识
    返回：完整的字节数组（6字节头 + 14字节数据）
    """
    # 转换速度、加速度为控制器单位
    max_vel = int(max_vel_degps * VEL_FACTOR)
    acc = int(acc_degps2 * ACC_FACTOR)
    min_vel_val = int(min_vel * VEL_FACTOR)  # 最小速度（单位同速度）
    # 数据包：通道标识(2) + 最小速度(4) + 加速度(4) + 最大速度(4)
    data = bytearray()
    data += channel.to_bytes(2, 'little')
    data += min_vel_val.to_bytes(4, 'little')
    data += acc.to_bytes(4, 'little')
    data += max_vel.to_bytes(4, 'little')
    # 消息头：ID(0x0413) + 数据长度(0x000E) + 目的地址(0x50|0x80) + 源地址(0x01)
    header = bytearray([0x13, 0x04, 0x0E, 0x00, 0xD0, 0x01])
    return header + data

def main():
    # 打开串口（根据实际端口修改，此处为COM10）
    ser = serial.Serial(
        port='COM11',#根据实际更改
        baudrate=115200,
        bytesize=8,
        parity=serial.PARITY_NONE,
        stopbits=1,
        xonxoff=0,
        rtscts=0,          # 通常USB虚拟串口无需硬件流控
        timeout=1
    )

    print(f"串口打开: {ser.is_open}")
    ser.flushInput()
    ser.flushOutput()

    # 1. 识别设备（可选）
    cmd_ident = bytearray([0x23, 0x02, 0x00, 0x00, 0x50, 0x01])  # MGMSG_MOD_IDENTIFY
    ser.write(cmd_ident)
    ser.flushInput()
    ser.flushOutput()
    time.sleep(0.5)

    # 2. 启用通道
    cmd_enable = bytearray([0x10, 0x02, 0x01, 0x01, 0x50, 0x01])  # MGMSG_MOD_SET_CHANENABLESTATE
    ser.write(cmd_enable)
    ser.flushInput()
    ser.flushOutput()
    time.sleep(0.5)

    # 3. 设置速度和加速度（例如：最大速度10 deg/s，加速度5 deg/s²）
    vel_cmd = build_set_velparams(max_vel_degps=10.0, acc_degps2=5.0)
    ser.write(vel_cmd)
    ser.flushInput()
    ser.flushOutput()
    time.sleep(0.5)

    # 4. （可选）归零
    print("归零中...")
    cmd_home = bytearray([0x43, 0x04, 0x01, 0x00, 0x50, 0x01])  # MGMSG_MOT_MOVE_HOME
    ser.write(cmd_home)
    ser.flushInput()
    ser.flushOutput()
    time.sleep(5)  # 等待归零完成（根据实际调整）

    # 5. 绝对移动到指定角度（例如45度）
    target_angle = 135.0
    print(f"移动到 {target_angle} 度...")
    move_cmd = build_move_absolute(target_angle)
    ser.write(move_cmd)
    ser.flushInput()
    ser.flushOutput()
    # 根据速度估算移动时间（粗略），此处等待5秒
    time.sleep(5)

    print("移动完成。")
    ser.close()

if __name__ == "__main__":
    main()