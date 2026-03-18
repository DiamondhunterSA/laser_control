import cv2
import numpy as np
import matplotlib.pyplot as plt

def analyze_laser_line(image_path, pixel_to_um=1.0):
    # 1. 加载图片并转为灰度
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if img is None:
        print("错误: 无法加载图片")
        return

    # 2. 预处理：轻微高斯模糊，减少表面粗糙度带来的高频噪声
    blurred = cv2.GaussianBlur(img, (5, 5), 0)

    # 3. 垂直投影定位线条 (寻找暗线)
    # 对每一行求和，暗线所在行的总和会是极小值
    projection = np.sum(blurred, axis=1)
    center_y = np.argmin(projection)
    
    # 定义检查区域（在中心行上下各取25像素）
    search_range = 25
    roi_y_start = max(0, center_y - search_range)
    roi_y_end = min(img.shape[0], center_y + search_range)

    # 4. 逐列扫描测量线宽
    widths = []
    # 为了提高性能和鲁棒性，每隔5个像素采样一次
    for x in range(0, img.shape[1], 5):
        profile = blurred[roi_y_start:roi_y_end, x].astype(float)
        
        # 计算一阶导数（梯度）
        gradient = np.diff(profile)
        
        # 暗线边缘特征：
        # 上边缘：亮 -> 暗 (梯度负极值)
        # 下边缘：暗 -> 亮 (梯度正极值)
        idx_top = np.argmin(gradient)
        idx_bottom = np.argmax(gradient)

        # --- 亚像素插值 (Parabolic Interpolation) ---
        def get_subpixel(grad_array, idx):
            if idx <= 0 or idx >= len(grad_array) - 1:
                return idx
            # 抛物线拟合公式
            y1, y2, y3 = grad_array[idx-1], grad_array[idx], grad_array[idx+1]
            denom = 2 * (y1 - 2*y2 + y3)
            if denom == 0: return idx
            delta = (y1 - y3) / denom
            return idx + delta

        sub_top = get_subpixel(gradient, idx_top)
        sub_bottom = get_subpixel(gradient, idx_bottom)

        pixel_width = sub_bottom - sub_top
        
        # 过滤掉明显的错误宽度（根据你的图片，宽度应大于5像素）
        if 5 < pixel_width < 100:
            widths.append(pixel_width)

    # 5. 结果统计
    if not widths:
        print("未检测到有效线条")
        return

    avg_width_px = np.mean(widths)
    std_width_px = np.std(widths)
    real_width = avg_width_px * pixel_to_um

    # 6. 可视化结果
    plt.figure(figsize=(12, 6))
    
    # 子图1：原图与检测线
    plt.subplot(1, 2, 1)
    plt.imshow(img, cmap='gray')
    plt.axhline(center_y, color='red', linestyle='--', label='Center Line')
    plt.axhline(center_y - avg_width_px/2, color='cyan', label='Detected Edge')
    plt.axhline(center_y + avg_width_px/2, color='cyan')
    plt.title(f"Detection (Avg: {avg_width_px:.2f} px)")
    plt.legend()

    # 子图2：中段截面的梯度分布
    plt.subplot(1, 2, 2)
    mid_x = img.shape[1] // 2
    sample_profile = blurred[roi_y_start:roi_y_end, mid_x].astype(float)
    sample_grad = np.diff(sample_profile)
    plt.plot(sample_grad, label='Gradient Profile')
    plt.axvline(np.argmin(sample_grad), color='r', alpha=0.5, label='Top Edge')
    plt.axvline(np.argmax(sample_grad), color='g', alpha=0.5, label='Bottom Edge')
    plt.title("Edge Gradient Analysis")
    plt.legend()

    print(f"--- 分析结果 ---")
    print(f"平均线宽 (像素): {avg_width_px:.3f} px")
    print(f"线宽标准差: {std_width_px:.3f} px")
    print(f"实际物理线宽: {real_width:.3f} (单位视标定而定)")
    
    plt.show()

# 使用示例
# image_path: 你的图片路径
# pixel_to_um: 你的相机标定系数（1个像素代表多少微米），若不确定先填1.0
analyze_laser_line('D:\ccd\screenshots\laser_line_X20_Y552_P0.0132W_20260310_134213.png', pixel_to_um=1.0)
