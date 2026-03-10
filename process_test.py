import cv2
import numpy as np
import os
import re
import csv
from pathlib import Path




def get_subpixel_peak(grad_array, idx):
    if idx <= 0 or idx >= len(grad_array) - 1:
        return idx
    y1, y2, y3 = grad_array[idx-1], grad_array[idx], grad_array[idx+1]
    denom = 2 * (y1 - 2*y2 + y3)
    if abs(denom) < 1e-6: return idx
    return idx + (y1 - y3) / denom

def process_single_image(img_path, debug=False):
    img = cv2.imread(str(img_path), cv2.IMREAD_GRAYSCALE)
    if img is None: return None, None
    
    # --- 改进1：使用自适应二值化 ---
    # 激光条纹背景可能明暗不均，自适应阈值能更好处理“靠边”的线条
    denoised = cv2.medianBlur(img, 7)
    thresh = cv2.adaptiveThreshold(denoised, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, 
                                   cv2.THRESH_BINARY_INV, 21, 10)
    
    # --- 改进2：基于“长宽比”而非绝对像素筛选 ---
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    valid_candidates = []
    for cnt in contours:
        x, y, w, h = cv2.boundingRect(cnt)
        aspect_ratio = w / float(h)
        # 线条应该是横向很长的，长宽比通常大于 5
        if w > 50 and aspect_ratio > 3:
            valid_candidates.append((cnt, x, y, w, h))
    
    if not valid_candidates: return None, None
    
    # 取最长的那条线
    main_cnt, x, y, w, h = max(valid_candidates, key=lambda b: b[3])

    # --- 改进3：拓宽 Y 轴剖面搜索范围 ---
    widths = []
    blurred = cv2.GaussianBlur(img, (5, 5), 0).astype(float)
    
    # 增加边缘裕度，防止倾斜导致采样点漏掉边缘
    margin = 30 
    for cur_x in range(x + 10, x + w - 10, 10):
        y_s, y_e = max(0, y - margin), min(img.shape[0], y + h + margin)
        profile = blurred[y_s:y_e, cur_x]
        
        if len(profile) < 10: continue
        grad = np.diff(profile)
        idx_t, idx_b = np.argmin(grad), np.argmax(grad)
        
        if idx_b > idx_t:
            # 亚像素插值
            sub_t = get_subpixel_peak(grad, idx_t)
            sub_b = get_subpixel_peak(grad, idx_b)
            width = sub_b - sub_t
            # 放宽宽度限制
            if 2 < width < 300:
                widths.append(width)

    if len(widths) < 3: return None, None # 降低最少采样点要求
    return np.mean(widths), np.std(widths)


'''
def get_subpixel_peak(grad_array, idx):
    """
    抛物线插值实现亚像素边缘定位
    y = ax^2 + bx + c
    """
    if idx <= 0 or idx >= len(grad_array) - 1:
        return idx
    y1, y2, y3 = grad_array[idx-1], grad_array[idx], grad_array[idx+1]
    
    # 分母：2 * (y1 - 2*y2 + y3)
    denom = 2 * (y1 - 2*y2 + y3)
    if abs(denom) < 1e-6: 
        return idx
    
    # 顶点偏移量计算
    return idx + (y1 - y3) / denom

def process_single_image(img_path):
    """
    核心算法：通过轮廓锁定条纹区域，并在区域内进行亚像素线宽测量
    """
    # 1. 读取图像
    img = cv2.imread(str(img_path), cv2.IMREAD_GRAYSCALE)
    if img is None: 
        return None, None
    
    # 2. 预处理：去除背景杂质
    # 使用中值滤波有效剔除细小的激光飞溅黑点，而不模糊条纹边缘
    denoised = cv2.medianBlur(img, 5)
    
    # 3. 定位条纹区域 (ROI)
    # 使用大津法(OTSU)自动二值化，寻找黑色条纹
    _, thresh = cv2.threshold(denoised, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
    
    # 寻找轮廓
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if not contours:
        return None, None
    
    # 筛选面积最大的轮廓（即条纹本体）
    main_contour = max(contours, key=cv2.contourArea)
    x, y, w, h = cv2.boundingRect(main_contour)
    
    # 过滤：如果检测到的物体太小（如只是个杂质），则跳过
    if w < 50 or h < 5:
        return None, None

    # 4. 精细测量
    widths = []
    # 预平滑用于梯度计算（减少单像素噪声）
    blurred = cv2.GaussianBlur(img, (5, 5), 0).astype(float)
    
    # 在条纹占据的 X 范围内采样，避开两端 10% 的边缘畸变区
    sample_start_x = x + int(w * 0.1)
    sample_end_x = x + int(w * 0.9)
    
    # 遍历采样列
    for cur_x in range(sample_start_x, sample_end_x, 5):
        # 提取当前列的 Y 方向剖面，高度适当延伸以覆盖边缘
        roi_y_up = max(0, y - 15)
        roi_y_down = min(img.shape[0], y + h + 15)
        profile = blurred[roi_y_up:roi_y_down, cur_x]
        
        # 计算一阶梯度 (寻找亮度变化最剧烈的地方)
        gradient = np.diff(profile)
        
        # 上边缘：由白变黑（梯度最小值/负向峰值）
        idx_top = np.argmin(gradient)
        # 下边缘：由黑变白（梯度最大值/正向峰值）
        idx_bottom = np.argmax(gradient)
        
        # 逻辑检查：上边缘必须在下边缘之上
        if idx_bottom > idx_top:
            # 亚像素修正
            sub_top = get_subpixel_peak(gradient, idx_top)
            sub_bottom = get_subpixel_peak(gradient, idx_bottom)
            
            line_width = sub_bottom - sub_top
            
            # 这里的阈值根据您的实际条纹宽度调整（通常在5-150像素之间）
            if 5 < line_width < 200:
                widths.append(line_width)
    
    # 5. 结果返回
    if len(widths) < 5: 
        return None, None
        
    return np.mean(widths), np.std(widths)
'''
def batch_process(folder_path, output_csv):
    """
    批量处理逻辑
    """
    pattern = re.compile(r'X(-?\d+)')
    results = []
    image_extensions = ('.jpg', '.png', '.bmp', '.tif', '.jpeg')
    
    folder = Path(folder_path)
    files = [f for f in folder.iterdir() if f.suffix.lower() in image_extensions]
    
    print(f"--- 开始处理 ---")
    print(f"目标目录: {folder_path}")
    print(f"发现图片: {len(files)} 张")

    for file_path in files:
        fname = file_path.name
        match = pattern.search(fname)
        x_velocity = match.group(1) if match else "Unknown"
        
        avg_w, std_w = process_single_image(file_path)
        
        if avg_w is not None:
            results.append({
                'filename': fname,
                'x_velocity': x_velocity,
                'avg_width_px': round(avg_w, 4),
                'std_dev_px': round(std_w, 4)
            })
            print(f"[成功] {fname} -> 宽度: {avg_w:.2f} px")
        else:
            print(f"[跳过] {fname} (无法识别有效条纹)")

    # 写入 CSV
    if results:
        keys = ['filename', 'x_velocity', 'avg_width_px', 'std_dev_px']
        with open(output_csv, 'w', newline='', encoding='utf-8') as f:
            dict_writer = csv.DictWriter(f, fieldnames=keys)
            dict_writer.writeheader()
            dict_writer.writerows(results)
        print(f"\n--- 处理完毕 ---\n结果已保存至: {output_csv}")
    else:
        print("\n未发现有效数据，未生成CSV。")

# --- 执行入口 ---
if __name__ == "__main__":
    # 配置您的路径
    # 建议使用 r'' 原始字符串防止路径转义错误
    input_folder = r'D:\\ccd\\phototest 1\\phototest 1' 
    output_name = 'laser_analysis_results.csv'

    if not os.path.exists(input_folder):
        print(f"错误: 找不到文件夹 {input_folder}")
    else:
        batch_process(input_folder, output_name)