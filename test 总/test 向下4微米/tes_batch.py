import cv2
import numpy as np
import pandas as pd
import re
import os
from pathlib import Path

def measure_line_width(image_path, threshold_val=80):
    """
    测量激光烧蚀线宽

    Args:
        image_path: 图片路径
        threshold_val: 二值化阈值

    Returns:
        (avg_width_px, std_width_px) 或错误信息
    """
    # 读取图像（支持中文路径）
    img = cv2.imdecode(np.fromfile(image_path, dtype=np.uint8), cv2.IMREAD_COLOR)
    if img is None:
        return None, None
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 二值化 (反转图像：让线变成白色 255，背景变成黑色 0)
    _, binary = cv2.threshold(gray, threshold_val, 255, cv2.THRESH_BINARY_INV)

    # 去噪：形态学闭运算
    kernel = np.ones((3, 3), np.uint8)
    binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel)

    # 测量线宽：对每一列计算白色像素的数量
    widths = np.sum(binary == 255, axis=0)

    # 过滤掉宽度为0的部分
    valid_widths = widths[widths > 0]

    if len(valid_widths) == 0:
        return None, None

    avg_width_px = np.mean(valid_widths)
    std_width_px = np.std(valid_widths)

    return avg_width_px, std_width_px


def extract_x_velocity(filename):
    """
    从文件名中提取X方向速度

    Args:
        filename: 文件名，如 'laser_line_X26_Y4797_20260208_181215.png'

    Returns:
        X方向速度 (整数)，如 26；如果解析失败返回 None
    """
    # 使用正则表达式提取 X后的数字
    match = re.search(r'X(\d+)', filename)
    if match:
        return int(match.group(1))
    return None


def batch_process(folder_path, threshold_val=80, output_excel='results.xlsx'):
    """
    批量处理文件夹中的激光烧蚀图片

    Args:
        folder_path: 图片文件夹路径
        threshold_val: 二值化阈值
        output_excel: 输出Excel文件名
    """
    folder = Path(folder_path)
    if not folder.exists():
        print(f"错误：文件夹不存在: {folder_path}")
        return

    # 获取所有PNG文件
    png_files = list(folder.glob('*.png'))
    if len(png_files) == 0:
        print(f"警告：在 {folder_path} 中未找到PNG文件")
        return

    print(f"找到 {len(png_files)} 个PNG文件")

    # 存储结果
    results = []

    for idx, png_file in enumerate(png_files, 1):
        filename = png_file.name
        print(f"[{idx}/{len(png_files)}] 处理: {filename}")

        # 提取X方向速度
        x_velocity = extract_x_velocity(filename)

        # 测量线宽
        avg_width, std_width = measure_line_width(str(png_file), threshold_val)

        if avg_width is not None:
            results.append({
                '文件名': filename,
                'X方向速度': x_velocity,
                '平均线宽(像素)': avg_width,
                '标准差(像素)': std_width
            })
            print(f"  -> X速度: {x_velocity}, 平均线宽: {avg_width:.2f}px, 标准差: {std_width:.2f}px")
        else:
            print(f"  -> 测量失败，可能需要调整阈值")

    # 保存到Excel
    if results:
        df = pd.DataFrame(results)
        output_path = folder / output_excel
        df.to_excel(output_path, index=False, engine='openpyxl')
        print(f"\n结果已保存到: {output_path}")
        print(f"\n统计摘要:")
        print(df.describe())
    else:
        print("\n警告：没有成功处理任何图片")


if __name__ == '__main__':
    # 设置参数
    FOLDER_PATH = 'd:/ccd/test 总/test 向下4微米'
    THRESHOLD_VAL = 80  # 根据实际情况调整
    OUTPUT_EXCEL = 'laser_line_width_results.xlsx'

    # 执行批量处理
    batch_process(FOLDER_PATH, THRESHOLD_VAL, OUTPUT_EXCEL)
