import cv2
import numpy as np
import matplotlib.pyplot as plt

def measure_line_width(image_path, threshold_val=100):
    # 1. 读取图像（支持中文路径）
    img = cv2.imdecode(np.fromfile(image_path, dtype=np.uint8), cv2.IMREAD_COLOR)
    if img is None:
        print(f"错误：无法读取图片文件 {image_path}")
        return "图片读取失败"
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 2. 二值化 (反转图像：让线变成白色 255，背景变成黑色 0)
    # 因为原图中线是深色的，背景是浅色的
    _, binary = cv2.threshold(gray, threshold_val, 255, cv2.THRESH_BINARY_INV)

    # 3. 去噪：形态学闭运算（填充线内部细小缝隙）
    kernel = np.ones((3,3), np.uint8)
    binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel)

    # 4. 测量线宽
    # 我们对每一列进行扫描，计算白色像素的数量
    widths = np.sum(binary == 255, axis=0)
    
    # 过滤掉宽度为0的部分（即没有线的地方）
    valid_widths = widths[widths > 0]

    if len(valid_widths) == 0:
        return "未检测到线条，请调整阈值。"

    avg_width_px = np.mean(valid_widths)
    std_width_px = np.std(valid_widths)

    return avg_width_px, std_width_px, binary, valid_widths

# --- 执行 ---
# 注意：你需要根据图片实际明暗调整 threshold_val
file_path = 'D:\\ccd\\screenshots\\med\\laser_line_X20_Y3795_P0.0634W_20260301_155821.png'
avg, std, processed_img, width_data = measure_line_width(file_path, 100)

print(f"平均线宽: {avg:.2f} 像素")
print(f"标准差: {std:.2f} 像素")

# 可视化结果
plt.figure(figsize=(12, 6))
plt.subplot(121), plt.imshow(processed_img, cmap='gray'), plt.title('Binarized Line')
plt.subplot(122), plt.plot(width_data), plt.title('Width Distribution (px)')
plt.ylabel('Width (pixels)'), plt.xlabel('Position along the line')
plt.show()
