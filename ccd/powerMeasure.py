# -*- coding: utf-8 -*-
"""
Created on Thu Dec 18 15:33:42 2025

@author: admin
"""

from TLPM import TLPM
from ctypes import c_uint32, byref, create_string_buffer, c_bool, c_int, c_double
import time


def find_devices():
    """查找并返回所有可用的功率计设备列表"""
    powermeter = TLPM()
    deviceCount = c_uint32()
    powermeter.findRsrc(byref(deviceCount))

    available_devices = []
    for i in range(deviceCount.value):
        resourceName = create_string_buffer(1024)
        powermeter.getRsrcName(c_int(i), resourceName)
        available_devices.append(resourceName.value.decode('utf-8'))
    
    return available_devices


def connect_power_meter(device_index=0):
    """
    连接到指定索引的功率计设备
    
    Args:
        device_index: 设备索引，默认为0（第一个设备）
    
    Returns:
        powermeter: TLPM对象，如果连接失败返回None
    """
    powermeter = TLPM()
    deviceCount = c_uint32()
    powermeter.findRsrc(byref(deviceCount))

    available_devices = []
    for i in range(deviceCount.value):
        resourceName = create_string_buffer(1024)
        powermeter.getRsrcName(c_int(i), resourceName)
        available_devices.append(resourceName.value.decode('utf-8'))

    if not available_devices:
        print("未找到任何设备！")
        return None

    if device_index >= len(available_devices):
        print(f"设备索引 {device_index} 超出范围！")
        return None

    resource_to_connect = create_string_buffer(available_devices[device_index].encode('utf-8'))
    powermeter.open(resource_to_connect, c_bool(True), c_bool(True))
    time.sleep(2)
    
    return powermeter


def measure_power(powermeter):
    """
    测量功率
    
    Args:
        powermeter: 已连接的TLPM对象
    
    Returns:
        float: 功率值（瓦特），测量失败返回None
    """
    if powermeter is None:
        print("功率计未连接！")
        return None
    
    try:
        power = c_double()
        powermeter.measPower(byref(power))
        return power.value
    except Exception as e:
        print(f"测量失败: {e}")
        return None


def close_power_meter(powermeter):
    """关闭功率计连接"""
    if powermeter is not None:
        try:
            powermeter.close()
        except Exception as e:
            print(f"关闭设备失败: {e}")


def get_power(readings=1, delay=0.5, device_index=0):
    """
    便捷函数：获取功率测量值
    
    Args:
        readings: 测量次数，取平均值
        delay: 每次测量间隔时间（秒）
        device_index: 设备索引
    
    Returns:
        float: 平均功率值（瓦特），失败返回None
    """
    powermeter = connect_power_meter(device_index)
    if powermeter is None:
        return None
    
    try:
        power_values = []
        for _ in range(readings):
            power = c_double()
            powermeter.measPower(byref(power))
            power_values.append(power.value)
            if readings > 1:
                time.sleep(delay)
        
        avg_power = sum(power_values) / len(power_values)
        return avg_power
    except Exception as e:
        print(f"测量失败: {e}")
        return None
    finally:
        close_power_meter(powermeter)


if __name__ == "__main__":
    print("Available devices:", find_devices())
    power = get_power()
    if power is not None:
        print(f"Power: {power} W")