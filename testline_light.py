import os
import cv2
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# 脚本所在目录，用于构建绝对路径
_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

def gaussian_func(x, a, mu, sigma, base):
    """定义高斯函数：用于拟合灰度剖面"""
    # a: 幅度, mu: 中心位置, sigma: 标准差, base: 背景基准灰度
    return a * np.exp(-(x - mu)**2 / (2 * sigma**2)) + base

def imread_cn(path):
    """支持中文路径的图片读取"""
    return cv2.imdecode(np.fromfile(path, dtype=np.uint8), cv2.IMREAD_GRAYSCALE)

def measure_line_width(image_path, roi_coords):
    # 1. 加载并转为灰度图（支持中文路径）
    img = imread_cn(image_path)
    if img is None:
        print(f"图片加载失败: {image_path}")
        return None

    # 2. 截取 ROI (感兴趣区域)
    # roi_coords: (y_start, y_end, x_start, x_end)
    y1, y2, x1, x2 = roi_coords
    roi = img[y1:y2, x1:x2]
    
    # 3. 多行平均投影 (关键步骤：将二维图像压成一维，抵消随机噪声)
    # 假设线条是水平的，我们对列进行平均，得到垂直方向的灰度分布
    profile = np.mean(roi, axis=1)
    x_data = np.arange(len(profile))

    # 4. 初始化拟合参数
    # 因为线条比背景暗，幅度 a 应该是负值
    base_guess = np.max(profile)
    a_guess = np.min(profile) - base_guess
    mu_guess = np.argmin(profile)
    sigma_guess = 5.0 # 初始猜一个宽度
    
    p0 = [a_guess, mu_guess, sigma_guess, base_guess]

    # 5. 执行高斯拟合 (亚像素精度)
    try:
        popt, _ = curve_fit(gaussian_func, x_data, profile, p0=p0)
        a, mu, sigma, base = popt
        
        # 6. 计算 FWHM (半高全宽)
        # FWHM = 2 * sqrt(2 * ln(2)) * sigma
        fwhm = 2.355 * abs(sigma)
        return fwhm

    except Exception as e:
        print(f"  拟合失败: {e}")
        return None

# --- 批量处理配置 ---
# ROI 坐标 [y_start, y_end, x_start, x_end]
my_roi = [600, 800, 150, 450]
# 待处理的图片文件夹
folder = r'D:\ccd\test 总\test 向上10微米'

files = sorted([f for f in os.listdir(folder) if f.lower().endswith('.png')])
print(f"找到 {len(files)} 张图片，开始批量处理...")
print(f"{'序号':<4} {'文件名':<52} {'线宽 FWHM (像素)'}")
print('-' * 75)

results = []
for i, f in enumerate(files, 1):
    path = os.path.join(folder, f)
    fwhm = measure_line_width(path, my_roi)
    if fwhm is not None:
        print(f"{i:<4} {f:<52} {fwhm:.4f} px")
        results.append(fwhm)
    else:
        print(f"{i:<4} {f:<52} 失败")

if results:
    print('-' * 75)
    print(f"{'平均线宽:':<57} {np.mean(results):.4f} px")
    print(f"{'标准差:':<57} {np.std(results):.4f} px")