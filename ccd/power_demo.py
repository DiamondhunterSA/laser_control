# -*- coding: utf-8 -*-
"""
power_demo.py - 演示如何调用 power_test 模块
"""

# 方式1：导入特定函数
from power_test import get_power, find_devices, connect_power_meter, measure_power, close_power_meter

# 方式2：导入整个模块
# import ccd.power_test as pm

# 示例1：查看可用设备
print("=== 查找设备 ===")
devices = find_devices()
print(f"可用设备: {devices}")

# 示例2：简单获取功率（自动连接、测量、关闭）
print("\n=== 简单测量 ===")
power = get_power()
if power is not None:
    print(f"功率: {power:.6f} W")

# 示例3：多次测量取平均
print("\n=== 多次测量 ===")
power_avg = get_power(readings=5, delay=0.5)
if power_avg is not None:
    print(f"平均功率: {power_avg:.6f} W")

# 示例4：手动控制连接和测量
print("\n=== 手动控制 ===")
pm = connect_power_meter()
if pm is not None:
    p1 = measure_power(pm)
    print(f"第1次: {p1:.6f} W")
    
    p2 = measure_power(pm)
    print(f"第2次: {p2:.6f} W")
    
    close_power_meter(pm)
    print("已关闭设备")

# 示例5：连接第二个设备（如果有）
# power = get_power(device_index=1)
