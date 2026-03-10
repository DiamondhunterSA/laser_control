import cv2
import numpy as np
import os
import re
import csv
from pathlib import Path

def get_subpixel_peak(grad_array, idx):
    """抛物线插值实现亚像素定位"""
    if idx <= 0 or idx >= len(grad_array) - 1:
        return idx
    y1, y2, y3 = grad_array[idx-1], grad_array[idx], grad_array[idx+1]
    denom = 2 * (y1 - 2*y2 + y3)
    if denom == 0: return idx
    return idx + (y1 - y3) / denom

def process_single_image(img_path):
    """核心算法：计算单张图片的线宽及标准差"""
    img = cv2.imread(str(img_path), cv2.IMREAD_GRAYSCALE)
    if img is None: return None, None
    
    # 预处理
    blurred = cv2.GaussianBlur(img, (5, 5), 0)
    
    # 垂直投影锁定线条纵向位置
    projection = np.sum(blurred, axis=1)
    center_y = np.argmin(projection)
    
    search_range = 30
    roi_y_start = max(0, center_y - search_range)
    roi_y_end = min(img.shape[0], center_y + search_range)
    
    widths = []
    # 沿水平方向步进采样
    for x in range(0, img.shape[1], 10):
        profile = blurred[roi_y_start:roi_y_end, x].astype(float)
        gradient = np.diff(profile)
        
        idx_top = np.argmin(gradient)
        idx_bottom = np.argmax(gradient)
        
        # 亚像素修正
        sub_top = get_subpixel_peak(gradient, idx_top)
        sub_bottom = get_subpixel_peak(gradient, idx_bottom)
        
        width = sub_bottom - sub_top
        # 过滤异常跳变点（根据您的图片特征，通常宽度在10-80像素）
        if 5 < width < 150:
            widths.append(width)
    
    if len(widths) < 10: return None, None
    return np.mean(widths), np.std(widths)

def batch_process(folder_path, output_csv):
    # 正则表达式匹配文件名中的X速度，例如 laser_line_X24_... 匹配 24
    pattern = re.compile(r'X(-?\d+)')
    
    results = []
    image_extensions = ('.jpg', '.png', '.bmp', '.tif')
    files = [f for f in Path(folder_path).iterdir() if f.suffix.lower() in image_extensions]
    
    print(f"开始处理，共发现 {len(files)} 张图片...")

    for file_path in files:
        fname = file_path.name
        # 提取X速度
        match = pattern.search(fname)
        x_velocity = match.group(1) if match else "Unknown"
        
        # 处理图片
        avg_w, std_w = process_single_image(file_path)
        
        if avg_w is not None:
            results.append({
                'filename': fname,
                'x_velocity': x_velocity,
                'avg_width_px': round(avg_w, 4),
                'std_dev_px': round(std_w, 4)
            })
            print(f"成功: {fname} -> 速度:{x_velocity}, 线宽:{avg_w:.2f}")
        else:
            print(f"跳过: {fname} (未能识别线条)")

    # 写入CSV
    keys = ['filename', 'x_velocity', 'avg_width_px', 'std_dev_px']
    with open(output_csv, 'w', newline='', encoding='utf-8') as f:
        dict_writer = csv.DictWriter(f, fieldnames=keys)
        dict_writer.writeheader()
        dict_writer.writerows(results)
    
    print(f"\n处理完毕！结果已保存至: {output_csv}")

# --- 执行 ---
# 请修改为您的图片文件夹路径
input_folder = 'D:\ccd\phototest 偏上\phototest 偏上' 
output_name = 'laser_analysis_results.csv'

if __name__ == "__main__":
    if not os.path.exists(input_folder):
        os.makedirs(input_folder)
        print(f"请将图片放入 {input_folder} 文件夹后再运行")
    else:
        batch_process(input_folder, output_name)
