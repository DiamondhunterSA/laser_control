import cv2
import numpy as np
import pandas as pd
import re
from pathlib import Path

def measure_line_width(image_path, threshold_val=80, vis_dir='None'):
    """
    测量激光烧蚀线宽，并可选择保存可视化中间图像

    Args:
        image_path: 图片路径
        threshold_val: 二值化阈值
        vis_dir: 可视化图像保存目录（如为None则不保存）

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

    # 如果需要保存可视化，先保存二值化后的图像
    if vis_dir is not None:
        vis_path = Path(vis_dir)
        vis_path.mkdir(parents=True, exist_ok=True)
        base_name = Path(image_path).stem
        # 保存二值化图像（尚未去噪）
        binary_path = vis_path / f"{base_name}_binary.png"
        # 使用imencode支持中文路径
        cv2.imencode('.png', binary)[1].tofile(str(binary_path))

    # 去噪：形态学闭运算
    kernel = np.ones((3, 3), np.uint8)
    binary_closed = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel)

    # 如果需要保存可视化，保存闭运算后的图像
    if vis_dir is not None:
        closed_path = vis_path / f"{base_name}_closed.png"
        cv2.imencode('.png', binary_closed)[1].tofile(str(closed_path))

    # 获取图像尺寸
    h, w = binary_closed.shape

    # 垂直裁剪：取自下而上 30% ~ 35% 的区域
    # 底部为图像底部（行索引大），顶部为图像顶部（行索引小）
    start_row = int(h * (1 - 0.38))  # 底部35%处对应的行（包含）
    end_row = int(h * (1 - 0.27))  # 底部30%处对应的行（不包含）
    if start_row >= end_row:  # 区间无效，测量失败
        return None, None
    cropped = binary_closed[start_row:end_row, :]

    # 测量线宽：对每一列计算白色像素的数量（基于裁剪区域）
    widths = np.sum(cropped == 255, axis=0)

    # 水平裁剪：只取左侧 3/5 区域（原有逻辑）
    left_width = int(w * 3 / 5)
    widths_left = widths[:left_width]

    # 过滤掉宽度为0的部分
    valid_widths = widths_left[widths_left > 6]

    if len(valid_widths) == 0:
        return None, None

    avg_width_px = np.mean(valid_widths)
    std_width_px = np.std(valid_widths)

    return avg_width_px, std_width_px


def extract_x_velocity(filename):
    """
    从文件名中提取X方向速度
    """
    match = re.search(r'X(\d+)', filename)
    if match:
        return int(match.group(1))
    return None


def batch_process(folder_path, threshold_val=80, output_excel='results.xlsx', save_vis=True):
    """
    批量处理文件夹中的激光烧蚀图片

    Args:
        folder_path: 图片文件夹路径
        threshold_val: 二值化阈值
        output_excel: 输出Excel文件名
        save_vis: 是否保存可视化中间图像
    """
    folder = Path(folder_path)
    if not folder.exists():
        print(f"错误：文件夹不存在: {folder_path}")
        return

    # 准备可视化保存目录
    vis_dir = folder / 'visualization' if save_vis else None
    if save_vis:
        vis_dir.mkdir(parents=True, exist_ok=True)
        print(f"可视化图像将保存到: {vis_dir}")

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

        # 测量线宽（传入vis_dir）
        avg_width, std_width = measure_line_width(str(png_file), threshold_val, vis_dir)

        if avg_width is not None:
            results.append({
                'file': filename,
                'x_value': x_velocity,
                'line_width': avg_width,
                'edge_blurriness': std_width
            })
            print(f"  -> X速度: {x_velocity}, 平均线宽: {avg_width:.2f}px, 标准差: {std_width:.2f}px")
        else:
            print(f"  -> 测量失败，可能需要调整阈值")

    # 保存到Excel
    if results:
        df = pd.DataFrame(results)
        output_path = Path('D:/ccd/') / output_excel
        output_path.parent.mkdir(parents=True, exist_ok=True)  # 确保输出目录存在
        df.to_excel(output_path, index=False, engine='openpyxl')
        print(f"\n结果已保存到: {output_path}")
        print(f"\n统计摘要:")
        print(df.describe())
    else:
        print("\n警告：没有成功处理任何图片")


if __name__ == '__main__':
    # 设置参数
    FOLDER_PATH = 'D:/ccd/ccd/screenshots'
    THRESHOLD_VAL = 80  # 根据实际情况调整
    OUTPUT_EXCEL = 'line_width_results.xlsx'

    # 执行批量处理（启用可视化保存）
    batch_process(FOLDER_PATH, THRESHOLD_VAL, OUTPUT_EXCEL, save_vis=True)