import os
import re
import cv2
import numpy as np
import pandas as pd
from pathlib import Path
import matplotlib.pyplot as plt
import openpyxl
from matplotlib.widgets import Slider, Button, RadioButtons
from scipy.signal import find_peaks, savgol_filter
import matplotlib.gridspec as gridspec
from scipy import stats
from scipy.ndimage import gaussian_filter1d
import matplotlib
# 尝试不同的后端
matplotlib.use('TkAgg')  # 尝试TkAgg后端
# matplotlib.use('Qt5Agg')  # 或者尝试Qt5Agg
# matplotlib.use('QtAgg')   # 或者QtAgg
# matplotlib.use('WXAgg')   # 或者WXAgg

# 提取文件
def parse_filename(filename):
    pattern = r'laser_line_X(\d+)_Y(\d+)_(\d{8})_(\d{6})'
    match = re.match(pattern, filename)

    if match:
        x_value = match.group(1)
        y_value = match.group(2)
        date = match.group(3)
        time = match.group(4)

        formatted_date = f"{date[:4]}-{date[4:6]}-{date[6:8]}"
        formatted_time = f"{time[:2]}:{time[2:4]}:{time[4:6]}"

        return {
            'original_filename': filename,
            'x_value': int(x_value),
            'y_value': int(y_value),
            'date': formatted_date,
            'time': formatted_time,
            'datetime': f"{formatted_date} {formatted_time}"
        }
    else:
        raise ValueError(f"文件名格式不正确: {filename}")

#分析图像中线条的强度剖面，寻找最佳的宽度测量方法
def analyze_intensity_profile(image_path, debug=True):
    # 读取图像
    img = cv2.imread(image_path)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 计算水平投影
    horizontal_projection = np.mean(gray, axis=1)

    if debug:
        fig, axes = plt.subplots(2, 3, figsize=(15, 10))

        # 1. 显示原始图像
        axes[0, 0].imshow(gray, cmap='gray')
        axes[0, 0].set_title('原始灰度图')
        axes[0, 0].axis('off')

        # 2. 显示水平投影
        axes[0, 1].plot(horizontal_projection, range(len(horizontal_projection)))
        axes[0, 1].set_xlabel('平均灰度值')
        axes[0, 1].set_ylabel('行')
        axes[0, 1].set_title('水平投影')
        axes[0, 1].invert_yaxis()

        # 3. 反转图像
        gray_inv = cv2.bitwise_not(gray)
        axes[0, 2].imshow(gray_inv, cmap='gray')
        axes[0, 2].set_title('反转灰度图')
        axes[0, 2].axis('off')

        # 4. 显示直方图
        axes[1, 0].hist(gray.ravel(), 256, [0, 256], color='black')
        axes[1, 0].set_xlabel('灰度值')
        axes[1, 0].set_ylabel('频数')
        axes[1, 0].set_title('灰度直方图')

        # 5. 显示梯度
        gradient = np.gradient(horizontal_projection)
        axes[1, 1].plot(gradient, range(len(gradient)))
        axes[1, 1].axvline(x=0, color='r', linestyle='--', alpha=0.5)
        axes[1, 1].set_xlabel('梯度值')
        axes[1, 1].set_ylabel('行')
        axes[1, 1].set_title('水平投影梯度')
        axes[1, 1].invert_yaxis()

        # 6. 显示二阶导数
        second_derivative = np.gradient(gradient)
        axes[1, 2].plot(second_derivative, range(len(second_derivative)))
        axes[1, 2].axvline(x=0, color='r', linestyle='--', alpha=0.5)
        axes[1, 2].set_xlabel('二阶导数')
        axes[1, 2].set_ylabel('行')
        axes[1, 2].set_title('二阶导数')
        axes[1, 2].invert_yaxis()

        plt.tight_layout()
        plt.show()

    # 分析强度分布特征
    inverted_projection = 255 - horizontal_projection
    smooth_projection = gaussian_filter1d(inverted_projection, sigma=3)

    # 寻找峰值（线条中心）
    peaks, properties = find_peaks(smooth_projection,
                                   height=np.mean(smooth_projection) * 1.5,
                                   distance=50,
                                   prominence=20)

    if len(peaks) > 0:
        main_peak = peaks[np.argmax(properties['peak_heights'])]

        # 分析峰值周围的强度分布
        peak_value = smooth_projection[main_peak]
        baseline = np.percentile(smooth_projection, 10)

        # 计算不同阈值下的宽度
        thresholds = [
            baseline + 0.1 * (peak_value - baseline),  # 10% 阈值
            baseline + 0.2 * (peak_value - baseline),  # 20% 阈值
            baseline + 0.3 * (peak_value - baseline),  # 30% 阈值
            baseline + 0.4 * (peak_value - baseline),  # 40% 阈值
            baseline + 0.5 * (peak_value - baseline),  # 50% 阈值 (FWHM)
            baseline + 0.6 * (peak_value - baseline),  # 60% 阈值
            baseline + 0.7 * (peak_value - baseline),  # 70% 阈值
            baseline + 0.8 * (peak_value - baseline),  # 80% 阈值
        ]

        widths = []
        for threshold in thresholds:
            # 找到阈值交叉点
            above_threshold = smooth_projection > threshold
            transitions = np.where(np.diff(above_threshold.astype(int)))[0]

            if len(transitions) >= 2:
                # 找到包含峰值的区间
                for i in range(0, len(transitions) - 1, 2):
                    if transitions[i] <= main_peak <= transitions[i + 1]:
                        width = transitions[i + 1] - transitions[i]
                        widths.append(width)
                        break

        return widths, main_peak, smooth_projection

    return [], None, smooth_projection


def advanced_interactive_debug(image_path):
    """
    高级交互式调试工具，特别优化线宽测量
    """
    # 读取图像
    img = cv2.imread(image_path)
    if img is None:
        print(f"无法读取图像: {image_path}")
        return None

    # 转换为灰度图
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    height, width = gray.shape

    # 创建图形
    fig = plt.figure(figsize=(28, 18),dpi=100)
    gs = gridspec.GridSpec(4, 6, height_ratios=[2, 1.5, 1, 0.5])

    # 创建子图
    ax_original = plt.subplot(gs[0, 0])
    ax_gray = plt.subplot(gs[0, 1])
    ax_binary = plt.subplot(gs[0, 2])
    ax_edges = plt.subplot(gs[0, 3])
    ax_result = plt.subplot(gs[0, 4])
    ax_cross_section = plt.subplot(gs[0, 5])

    ax_projection = plt.subplot(gs[1, :2])
    ax_derivative = plt.subplot(gs[1, 2:4])
    ax_width_analysis = plt.subplot(gs[1, 4:])

    ax_multiple_profiles = plt.subplot(gs[2, :])
    ax_stats = plt.subplot(gs[3, :])
    ax_stats.axis('off')

    # 初始参数
    init_params = {
        'threshold': 140,
        'threshold_method': 'fixed',
        'morph_kernel': 5,
        'gaussian_blur': 4,
        'canny_low': 23.378734622144094,
        'canny_high': 83.63063854715875,
        'edge_threshold': 0.5,
        'width_method': 'fwhm',
        'width_threshold': 0.5,
        'contrast_enhance': 1.6869752001562195,
        'invert': True,
        'roi_height': 100,
        'smooth_sigma': 4.0
    }

    # 存储中间结果
    global_state = {
        'current_params': init_params.copy(),
        'original_img': img,
        'gray': gray,
        'detected_widths': [],
        'best_width': None,
        'best_y': None
    }

    # 创建滑动条区域
    axcolor = 'lightgoldenrodyellow'
    slider_height = 0.02
    slider_start = 0.02
    slider_spacing = 0.025

    # 阈值相关滑动条
    ax_thresh = plt.axes([0.15, slider_start + slider_spacing * 0, 0.3, slider_height], facecolor=axcolor)
    ax_contrast = plt.axes([0.15, slider_start + slider_spacing * 1, 0.3, slider_height], facecolor=axcolor)
    ax_gaussian = plt.axes([0.15, slider_start + slider_spacing * 2, 0.3, slider_height], facecolor=axcolor)
    ax_morph = plt.axes([0.15, slider_start + slider_spacing * 3, 0.3, slider_height], facecolor=axcolor)

    # 边缘检测滑动条
    ax_canny_low = plt.axes([0.15, slider_start + slider_spacing * 4, 0.3, slider_height], facecolor=axcolor)
    ax_canny_high = plt.axes([0.15, slider_start + slider_spacing * 5, 0.3, slider_height], facecolor=axcolor)
    ax_edge_thresh = plt.axes([0.15, slider_start + slider_spacing * 6, 0.3, slider_height], facecolor=axcolor)

    # 宽度测量滑动条
    ax_width_thresh = plt.axes([0.15, slider_start + slider_spacing * 7, 0.3, slider_height], facecolor=axcolor)
    ax_roi_height = plt.axes([0.15, slider_start + slider_spacing * 8, 0.3, slider_height], facecolor=axcolor)
    ax_smooth_sigma = plt.axes([0.15, slider_start + slider_spacing * 9, 0.3, slider_height], facecolor=axcolor)

    # 创建滑动条
    sliders = {}
    sliders['threshold'] = Slider(ax_thresh, '阈值', 0, 255, valinit=init_params['threshold'])
    sliders['contrast_enhance'] = Slider(ax_contrast, '对比度增强', 1.0, 5.0, valinit=init_params['contrast_enhance'])
    sliders['gaussian_blur'] = Slider(ax_gaussian, '高斯模糊', 0, 15, valinit=init_params['gaussian_blur'], valstep=2)
    sliders['morph_kernel'] = Slider(ax_morph, '形态学核', 1, 20, valinit=init_params['morph_kernel'])
    sliders['canny_low'] = Slider(ax_canny_low, 'Canny低阈值', 0, 255, valinit=init_params['canny_low'])
    sliders['canny_high'] = Slider(ax_canny_high, 'Canny高阈值', 0, 255, valinit=init_params['canny_high'])
    sliders['edge_threshold'] = Slider(ax_edge_thresh, '边缘阈值', 0.0, 1.0, valinit=init_params['edge_threshold'])
    sliders['width_threshold'] = Slider(ax_width_thresh, '宽度阈值', 0.1, 0.9, valinit=init_params['width_threshold'])
    sliders['roi_height'] = Slider(ax_roi_height, 'ROI高度', 10, 300, valinit=init_params['roi_height'])
    sliders['smooth_sigma'] = Slider(ax_smooth_sigma, '平滑强度', 0.0, 10.0, valinit=init_params['smooth_sigma'])

    # 创建单选框
    radio_ax1 = plt.axes([0.5, slider_start, 0.12, 0.15])
    radio1 = RadioButtons(radio_ax1, ('固定阈值', 'OTSU', '自适应'), active=0)

    radio_ax2 = plt.axes([0.5, slider_start + 0.16, 0.12, 0.15])
    radio2 = RadioButtons(radio_ax2, ('FWHM', '边缘检测', '多个阈值'), active=0)

    radio_ax3 = plt.axes([0.5, slider_start + 0.32, 0.12, 0.12])
    radio3 = RadioButtons(radio_ax3, ('反转', '不反转'), active=0)

    # 创建按钮
    button_ax1 = plt.axes([0.65, slider_start, 0.1, 0.05])
    reset_button = Button(button_ax1, '重置', color=axcolor, hovercolor='0.975')

    button_ax2 = plt.axes([0.65, slider_start + 0.06, 0.1, 0.05])
    export_button = Button(button_ax2, '导出参数', color=axcolor, hovercolor='0.975')

    button_ax3 = plt.axes([0.65, slider_start + 0.12, 0.1, 0.05])
    analyze_button = Button(button_ax3, '分析轮廓', color=axcolor, hovercolor='0.975')

    def update_images():
        # 获取参数和图像
        params = global_state['current_params']
        original_img = global_state['original_img']
        gray_img = global_state['gray']

        # 获取图像尺寸
        height, width = original_img.shape[:2]

        params = global_state['current_params']
        gray_img = global_state['gray']

        # 增强对比度
        if params['contrast_enhance'] > 1.0:
            gray_enhanced = cv2.convertScaleAbs(gray_img, alpha=params['contrast_enhance'], beta=0)
        else:
            gray_enhanced = gray_img.copy()

        # 应用高斯模糊
        blur_size = int(params['gaussian_blur'])
        if blur_size > 0 and blur_size % 2 == 1:
            gray_blur = cv2.GaussianBlur(gray_enhanced, (blur_size, blur_size), 0)
        else:
            gray_blur = gray_enhanced.copy()

        # 是否反转图像
        if params['invert']:
            gray_processed = cv2.bitwise_not(gray_blur)
        else:
            gray_processed = gray_blur.copy()

        # 二值化
        if params['threshold_method'] == 'fixed':
            _, binary = cv2.threshold(gray_processed, params['threshold'], 255, cv2.THRESH_BINARY)
        elif params['threshold_method'] == 'OTSU':
            _, binary = cv2.threshold(gray_processed, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
        else:  # adaptive
            binary = cv2.adaptiveThreshold(gray_processed, 255,
                                           cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
                                           cv2.THRESH_BINARY, 11, 2)

        # 形态学操作
        kernel_size = params['morph_kernel']
        if kernel_size > 0:
            kernel_horizontal = np.ones((1, kernel_size), np.uint8)
            kernel_vertical = np.ones((3, 1), np.uint8)
            binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel_horizontal)
            binary = cv2.morphologyEx(binary, cv2.MORPH_OPEN, kernel_vertical)

        # Canny边缘检测
        if params['canny_high'] > params['canny_low']:
            edges = cv2.Canny(gray_processed, params['canny_low'], params['canny_high'])
        else:
            edges = np.zeros_like(gray_processed)

        # 使用多种方法测量线宽
        all_widths = []
        all_methods = []

        # 方法1: 水平投影法
        horizontal_projection = np.mean(gray_processed, axis=1)
        smooth_projection = gaussian_filter1d(horizontal_projection, sigma=params['smooth_sigma'])

        # 寻找峰值
        peaks, properties = find_peaks(smooth_projection,
                                       height=np.mean(smooth_projection) * 1.5,
                                       distance=params['roi_height'] // 2,
                                       prominence=10)

        if len(peaks) > 0:
            # 选择最高的峰值
            main_peak_idx = peaks[np.argmax(properties['peak_heights'])]
            peak_value = smooth_projection[main_peak_idx]
            baseline = np.percentile(smooth_projection, 10)

            # 使用当前选择的阈值方法计算宽度
            threshold_value = baseline + params['width_threshold'] * (peak_value - baseline)

            # 找到阈值交叉点
            above_threshold = smooth_projection > threshold_value
            transitions = np.where(np.diff(above_threshold.astype(int)))[0]

            if len(transitions) >= 2:
                # 找到包含峰值的区间
                for i in range(0, len(transitions) - 1, 2):
                    if transitions[i] <= main_peak_idx <= transitions[i + 1]:
                        width = transitions[i + 1] - transitions[i]
                        all_widths.append(width)
                        all_methods.append(f'投影阈值{params["width_threshold"]:.1f}')
                        break

        # 方法2: 边缘检测法
        edge_rows = np.where(np.mean(edges, axis=1) > params['edge_threshold'] * 255)[0]
        if len(edge_rows) > 10:
            # 分组连续的边缘行
            edge_groups = []
            current_group = []

            for row in edge_rows:
                if not current_group or row == current_group[-1] + 1:
                    current_group.append(row)
                else:
                    if len(current_group) > 5:
                        edge_groups.append(current_group)
                    current_group = [row]

            if current_group and len(current_group) > 5:
                edge_groups.append(current_group)

            # 计算每组的高度
            group_heights = [len(group) for group in edge_groups]
            if group_heights:
                edge_width = np.median(group_heights)
                all_widths.append(edge_width)
                all_methods.append('边缘检测')

        # 方法3: 多个阈值法
        if len(peaks) > 0:
            thresholds_test = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8]
            widths_test = []

            for thresh_ratio in thresholds_test:
                threshold_value = baseline + thresh_ratio * (peak_value - baseline)
                above_threshold = smooth_projection > threshold_value
                transitions = np.where(np.diff(above_threshold.astype(int)))[0]

                if len(transitions) >= 2:
                    for i in range(0, len(transitions) - 1, 2):
                        if transitions[i] <= main_peak_idx <= transitions[i + 1]:
                            widths_test.append(transitions[i + 1] - transitions[i])
                            break

            if widths_test:
                # 取中位数作为最终宽度
                multi_width = np.median(widths_test)
                all_widths.append(multi_width)
                all_methods.append('多阈值中位数')

        # 选择最佳宽度
        best_width = None
        if all_widths:
            # 根据方法优先级选择
            if len(all_widths) >= 2:
                # 如果多个方法结果相近，取平均值
                if np.std(all_widths) / np.mean(all_widths) < 0.3:
                    best_width = np.mean(all_widths)
                else:
                    # 否则取最小值（避免过度估计）
                    best_width = min(all_widths)
            else:
                best_width = all_widths[0]

        # 更新全局状态
        global_state['detected_widths'] = all_widths
        global_state['best_width'] = best_width
        global_state['best_y'] = main_peak_idx if len(peaks) > 0 else None

        # 更新原始图像显示
        ax_original.clear()
        ax_original.imshow(cv2.cvtColor(global_state['original_img'], cv2.COLOR_BGR2RGB))
        ax_original.set_title('原始图像')
        ax_original.axis('off')

        # 更新灰度图像显示
        ax_gray.clear()
        ax_gray.imshow(gray_processed, cmap='gray')
        ax_gray.set_title('处理后的灰度图')
        ax_gray.axis('off')

        # 更新二值化图像显示
        ax_binary.clear()
        ax_binary.imshow(binary, cmap='gray')
        ax_binary.set_title(f'二值化 ({params["threshold_method"]})')
        ax_binary.axis('off')

        # 更新边缘检测图像
        ax_edges.clear()
        ax_edges.imshow(edges, cmap='gray')
        ax_edges.set_title('Canny边缘检测')
        ax_edges.axis('off')

        # 更新结果图像
        ax_result.clear()
        result_img = global_state['original_img'].copy()

        if global_state['best_y'] is not None and global_state['best_width'] is not None:
            y = int(global_state['best_y'])
            w = int(global_state['best_width'])

            # 绘制检测到的线条
            cv2.line(result_img, (0, y), (width, y), (0, 255, 0), 3)
            cv2.line(result_img, (0, y - w // 2), (width, y - w // 2), (255, 0, 0), 1)
            cv2.line(result_img, (0, y + w // 2), (width, y + w // 2), (255, 0, 0), 1)

            # 绘制ROI区域
            roi_half = params['roi_height'] // 2
            cv2.rectangle(result_img, (0, y - roi_half), (width, y + roi_half), (0, 0, 255), 2)

        ax_result.imshow(cv2.cvtColor(result_img, cv2.COLOR_BGR2RGB))
        result_title = '最终结果'
        if global_state['best_width'] is not None:
            result_title += f'\n宽度={global_state["best_width"]:.1f}像素'
        ax_result.set_title(result_title)
        ax_result.axis('off')

        # 更新横截面显示
        ax_cross_section.clear()
        if global_state['best_y'] is not None:
            y = int(global_state['best_y'])
            roi_half = min(50, params['roi_height'] // 2)
            start = max(0, y - roi_half)
            end = min(height, y + roi_half)

            if end > start:
                profile = np.mean(gray_processed[start:end, :], axis=1)
                ax_cross_section.plot(profile, range(start, end))

                if global_state['best_width'] is not None:
                    ax_cross_section.axhline(y=y, color='g', linestyle='-', linewidth=2)
                    ax_cross_section.axhline(y=y - global_state['best_width'] // 2, color='b', linestyle='--')
                    ax_cross_section.axhline(y=y + global_state['best_width'] // 2, color='b', linestyle='--')

                ax_cross_section.set_xlabel('灰度值')
                ax_cross_section.set_ylabel('行')
                ax_cross_section.set_title('横截面')
                ax_cross_section.invert_yaxis()
                ax_cross_section.grid(True, alpha=0.3)

        # 更新投影图
        ax_projection.clear()
        ax_projection.plot(horizontal_projection, range(len(horizontal_projection)), 'b-', alpha=0.5, label='原始')
        ax_projection.plot(smooth_projection, range(len(smooth_projection)), 'r-', linewidth=2, label='平滑后')

        if len(peaks) > 0:
            ax_projection.plot(smooth_projection[peaks], peaks, 'ro', markersize=8, label='峰值')
            if global_state['best_y'] is not None and global_state['best_width'] is not None:
                y = global_state['best_y']
                threshold_value = baseline + params['width_threshold'] * (peak_value - baseline)

                ax_projection.axhline(y=y, color='g', linestyle='-', linewidth=2)
                ax_projection.axhline(y=y - global_state['best_width'] // 2, color='orange', linestyle='--')
                ax_projection.axhline(y=y + global_state['best_width'] // 2, color='orange', linestyle='--')
                ax_projection.axvline(x=threshold_value, color='purple', linestyle=':', alpha=0.5)

        ax_projection.set_xlabel('灰度值')
        ax_projection.set_ylabel('行')
        ax_projection.set_title('水平投影')
        ax_projection.legend(loc='upper right')
        ax_projection.invert_yaxis()
        ax_projection.grid(True, alpha=0.3)

        # 更新导数图
        ax_derivative.clear()
        derivative = np.gradient(smooth_projection)
        second_derivative = np.gradient(derivative)

        ax_derivative.plot(derivative, range(len(derivative)), 'b-', label='一阶导数')
        ax_derivative.plot(second_derivative, range(len(second_derivative)), 'r-', alpha=0.7, label='二阶导数')
        ax_derivative.axvline(x=0, color='k', linestyle='--', alpha=0.3)

        if global_state['best_y'] is not None:
            y = global_state['best_y']
            ax_derivative.axhline(y=y, color='g', linestyle='-', linewidth=2)

        ax_derivative.set_xlabel('导数值')
        ax_derivative.set_ylabel('行')
        ax_derivative.set_title('导数分析')
        ax_derivative.legend(loc='upper right')
        ax_derivative.invert_yaxis()
        ax_derivative.grid(True, alpha=0.3)

        # 更新宽度分析图
        ax_width_analysis.clear()
        if all_widths:
            methods_display = all_methods
            widths_display = all_widths

            bars = ax_width_analysis.bar(range(len(widths_display)), widths_display)
            ax_width_analysis.set_xticks(range(len(widths_display)))
            ax_width_analysis.set_xticklabels(methods_display, rotation=45, ha='right')
            ax_width_analysis.set_ylabel('宽度(像素)')
            ax_width_analysis.set_title('不同方法的宽度测量')

            # 标注数值
            for i, (bar, width_val) in enumerate(zip(bars, widths_display)):
                ax_width_analysis.text(bar.get_x() + bar.get_width() / 2, bar.get_height() + 0.5,
                                       f'{width_val:.1f}', ha='center', va='bottom', fontsize=9)

            if global_state['best_width'] is not None:
                ax_width_analysis.axhline(y=global_state['best_width'], color='r', linestyle='--',
                                          label=f'最佳: {global_state["best_width"]:.1f}')
                ax_width_analysis.legend()

        # 更新多个剖面图
        ax_multiple_profiles.clear()
        if global_state['best_y'] is not None:
            y = int(global_state['best_y'])
            roi_half = min(100, params['roi_height'] // 2)
            start = max(0, y - roi_half)
            end = min(height, y + roi_half)

            # 在多个列位置采样
            sample_cols = np.linspace(0, width - 1, 10, dtype=int)

            for i, col in enumerate(sample_cols):
                profile = gray_processed[start:end, col]
                offset = i * 50  # 偏移量以便区分
                ax_multiple_profiles.plot(profile + offset, range(start, end), label=f'列{col}')

            if global_state['best_width'] is not None:
                ax_multiple_profiles.axhline(y=y, color='k', linestyle='-', linewidth=2)
                ax_multiple_profiles.axhline(y=y - global_state['best_width'] // 2, color='k', linestyle='--',
                                             alpha=0.5)
                ax_multiple_profiles.axhline(y=y + global_state['best_width'] // 2, color='k', linestyle='--',
                                             alpha=0.5)

            ax_multiple_profiles.set_xlabel('灰度值（偏移后）')
            ax_multiple_profiles.set_ylabel('行')
            ax_multiple_profiles.set_title('多个垂直剖面')
            ax_multiple_profiles.invert_yaxis()
            ax_multiple_profiles.grid(True, alpha=0.3)

        # 更新统计信息
        ax_stats.clear()
        ax_stats.axis('off')

        stats_text = f"图像尺寸: {width}×{height}\n"
        stats_text += f"平均灰度: {np.mean(gray):.1f}\n"
        stats_text += f"灰度标准差: {np.std(gray):.1f}\n"

        if len(peaks) > 0:
            stats_text += f"检测到的峰值: {len(peaks)}\n"
            if 'peak_heights' in properties:
                stats_text += f"峰值高度范围: {np.min(properties['peak_heights']):.1f}-{np.max(properties['peak_heights']):.1f}\n"

        if global_state['detected_widths']:
            stats_text += f"\n宽度测量结果:\n"
            for method, width_val in zip(all_methods, all_widths):
                stats_text += f"  {method}: {width_val:.1f}像素\n"

            stats_text += f"\n统计:\n"
            stats_text += f"  平均值: {np.mean(all_widths):.1f}像素\n"
            stats_text += f"  中位数: {np.median(all_widths):.1f}像素\n"
            stats_text += f"  最小值: {np.min(all_widths):.1f}像素\n"
            stats_text += f"  最大值: {np.max(all_widths):.1f}像素\n"
            stats_text += f"  标准差: {np.std(all_widths):.1f}像素\n"

        if global_state['best_width'] is not None:
            stats_text += f"\n最佳估计宽度: {global_state['best_width']:.1f}像素\n"

        ax_stats.text(0, 0.9, "统计信息:", fontsize=12, fontweight='bold')
        ax_stats.text(0.05, 0.7, stats_text, fontsize=10, verticalalignment='top')

        fig.canvas.draw_idle()

    def update_slider(val):
        """更新参数值"""
        for key, slider in sliders.items():
            global_state['current_params'][key] = slider.val
        update_images()

    def threshold_method_handler(label):
        """处理阈值方法选项"""
        if label == '固定阈值':
            global_state['current_params']['threshold_method'] = 'fixed'
        elif label == 'OTSU':
            global_state['current_params']['threshold_method'] = 'OTSU'
        elif label == '自适应':
            global_state['current_params']['threshold_method'] = 'adaptive'
        update_images()

    def width_method_handler(label):
        """处理宽度方法选项"""
        if label == 'FWHM':
            global_state['current_params']['width_method'] = 'fwhm'
        elif label == '边缘检测':
            global_state['current_params']['width_method'] = 'edge'
        elif label == '多个阈值':
            global_state['current_params']['width_method'] = 'multi'
        update_images()

    def invert_handler(label):
        """处理反转选项"""
        global_state['current_params']['invert'] = (label == '反转')
        update_images()

    def reset(event):
        """重置所有参数"""
        for key, val in init_params.items():
            global_state['current_params'][key] = val
            if key in sliders:
                sliders[key].set_val(val)
        radio1.set_active(0)
        radio2.set_active(0)
        radio3.set_active(0)
        update_images()

    def export_params(event):
        """导出当前参数"""
        params = global_state['current_params']
        params_str = "\n".join([f"{key}: {value}" for key, value in params.items()])
        print("\n" + "=" * 50)
        print("当前参数配置:")
        print("=" * 50)
        print(params_str)
        print("=" * 50)

        if global_state['best_width'] is not None:
            print(f"\n最佳宽度估计: {global_state['best_width']:.1f}像素")

        # 保存到文件
        with open('optimized_threshold_params.txt', 'w') as f:
            f.write(params_str)
            if global_state['best_width'] is not None:
                f.write(f"\n最佳宽度: {global_state['best_width']:.1f}像素")
        print("参数已保存到 optimized_threshold_params.txt")

    def analyze_profile(event):
        """分析强度剖面"""
        widths, peak, profile = analyze_intensity_profile(image_path, debug=True)
        if widths:
            print(f"\n强度剖面分析结果:")
            print(f"检测到的峰值位置: {peak}")
            print(f"不同阈值下的宽度: {widths}")
            print(f"推荐宽度(取中位数): {np.median(widths):.1f}像素")

    # 连接事件
    for slider in sliders.values():
        slider.on_changed(update_slider)

    radio1.on_clicked(threshold_method_handler)
    radio2.on_clicked(width_method_handler)
    radio3.on_clicked(invert_handler)
    reset_button.on_clicked(reset)
    export_button.on_clicked(export_params)
    analyze_button.on_clicked(analyze_profile)

    # 初始显示
    update_images()

    plt.show()

    # 返回最佳参数
    return global_state['current_params'], global_state['best_width']

#    精确测量黑色水平线的宽度
def precise_line_width_detection(image_path, params=None, debug=False):
    if params is None:
        params = {
            'threshold': 120,
            'threshold_method': 'fixed',
            'gaussian_blur': 5,
            'morph_kernel': 5,
            'contrast_enhance': 2.0,
            'smooth_sigma': 3.0,
            'width_threshold': 0.5,
            'invert': True
        }

    # 读取图像
    img = cv2.imread(image_path)
    if img is None:
        print(f"无法读取图像: {image_path}")
        return None, None

    # 转换为灰度图
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    height, width = gray.shape

    # 增强对比度
    if params['contrast_enhance'] > 1.0:
        gray_enhanced = cv2.convertScaleAbs(gray, alpha=params['contrast_enhance'], beta=0)
    else:
        gray_enhanced = gray.copy()

    # 应用高斯模糊
    blur_size = int(params['gaussian_blur'])
    if blur_size > 0 and blur_size % 2 == 1:
        gray_blur = cv2.GaussianBlur(gray_enhanced, (blur_size, blur_size), 0)
    else:
        gray_blur = gray_enhanced.copy()

    # 是否反转图像
    if params['invert']:
        gray_processed = cv2.bitwise_not(gray_blur)
    else:
        gray_processed = gray_blur.copy()

    # 计算水平投影
    horizontal_projection = np.mean(gray_processed, axis=1)

    # 平滑投影
    smooth_projection = gaussian_filter1d(horizontal_projection, sigma=params['smooth_sigma'])

    # 寻找峰值
    peaks, properties = find_peaks(smooth_projection,
                                   height=np.mean(smooth_projection) * 1.5,
                                   distance=100,
                                   prominence=10)

    if len(peaks) == 0:
        print(f"未检测到明显的峰值: {image_path}")
        return None, None

    # 选择最高的峰值
    main_peak_idx = peaks[np.argmax(properties['peak_heights'])]
    peak_value = smooth_projection[main_peak_idx]
    baseline = np.percentile(smooth_projection, 10)

    # 使用多个阈值计算宽度，然后选择最合理的
    thresholds = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8]
    widths = []

    for thresh_ratio in thresholds:
        threshold_value = baseline + thresh_ratio * (peak_value - baseline)
        above_threshold = smooth_projection > threshold_value
        transitions = np.where(np.diff(above_threshold.astype(int)))[0]

        if len(transitions) >= 2:
            # 找到包含峰值的区间
            for i in range(0, len(transitions) - 1, 2):
                if transitions[i] <= main_peak_idx <= transitions[i + 1]:
                    width = transitions[i + 1] - transitions[i]
                    widths.append(width)
                    break

    if not widths:
        print(f"无法计算宽度: {image_path}")
        return None, None

    # 选择最合适的宽度（排除异常值）
    widths_array = np.array(widths)
    q1 = np.percentile(widths_array, 25)
    q3 = np.percentile(widths_array, 75)
    iqr = q3 - q1

    # 使用IQR过滤异常值
    lower_bound = q1 - 1.5 * iqr
    upper_bound = q3 + 1.5 * iqr
    filtered_widths = widths_array[(widths_array >= lower_bound) & (widths_array <= upper_bound)]

    if len(filtered_widths) == 0:
        filtered_widths = widths_array

    # 选择中位数作为最终宽度
    final_width = np.median(filtered_widths)

    # 计算线条边界
    # 使用40%阈值（比FWHM更严格）
    threshold_value = baseline + 0.4 * (peak_value - baseline)
    above_threshold = smooth_projection > threshold_value
    transitions = np.where(np.diff(above_threshold.astype(int)))[0]

    left_edge = main_peak_idx
    right_edge = main_peak_idx

    if len(transitions) >= 2:
        for i in range(0, len(transitions) - 1, 2):
            if transitions[i] <= main_peak_idx <= transitions[i + 1]:
                left_edge = transitions[i]
                right_edge = transitions[i + 1]
                break

    # 创建轮廓
    contour = np.array([[[0, left_edge],
                         [width, left_edge],
                         [width, right_edge],
                         [0, right_edge]]], dtype=np.int32)

    line_contours = [{
        'contour': contour,
        'width': float(final_width),
        'narrow_width': float(right_edge - left_edge),  # 使用更严格阈值计算的宽度
        'fwhm_width': float(widths[4] if len(widths) > 4 else final_width),  # FWHM宽度
        'length': float(width),
        'center_y': float((left_edge + right_edge) // 2),
        'top_edge': int(left_edge),
        'bottom_edge': int(right_edge),
        'peak_position': int(main_peak_idx),
        'type': 'precise_horizontal_line'
    }]

    if debug:
        print(f"\n精确宽度测量结果:")
        print(f"  峰值位置: {main_peak_idx}")
        print(f"  峰值强度: {peak_value:.1f}")
        print(f"  基线强度: {baseline:.1f}")
        print(f"  不同阈值宽度: {widths}")
        print(f"  过滤后宽度: {filtered_widths}")
        print(f"  最终宽度(中位数): {final_width:.1f}像素")
        print(f"  严格阈值宽度(40%): {right_edge - left_edge:.1f}像素")

        # 可视化
        fig, axes = plt.subplots(1, 3, figsize=(15, 5))

        # 显示图像和检测结果
        img_with_line = img.copy()
        cv2.line(img_with_line, (0, main_peak_idx), (width, main_peak_idx), (0, 255, 0), 3)
        cv2.line(img_with_line, (0, left_edge), (width, left_edge), (255, 0, 0), 2)
        cv2.line(img_with_line, (0, right_edge), (width, right_edge), (255, 0, 0), 2)
        axes[0].imshow(cv2.cvtColor(img_with_line, cv2.COLOR_BGR2RGB))
        axes[0].set_title(f'检测结果\n宽度={final_width:.1f}像素')
        axes[0].axis('off')

        # 显示投影和阈值
        axes[1].plot(smooth_projection, range(len(smooth_projection)), 'b-', linewidth=2, label='平滑投影')
        axes[1].axvline(x=threshold_value, color='r', linestyle='--', label='40%阈值')
        axes[1].axvline(x=baseline + 0.5 * (peak_value - baseline), color='g', linestyle=':', label='50%阈值(FWHM)')
        axes[1].axhline(y=main_peak_idx, color='k', linestyle='-', alpha=0.5)
        axes[1].axhline(y=left_edge, color='r', linestyle='--', alpha=0.7)
        axes[1].axhline(y=right_edge, color='r', linestyle='--', alpha=0.7)
        axes[1].set_xlabel('灰度值')
        axes[1].set_ylabel('行')
        axes[1].set_title('投影分析')
        axes[1].legend()
        axes[1].invert_yaxis()

        # 显示宽度比较
        threshold_labels = ['10%', '20%', '30%', '40%', '50%', '60%', '70%', '80%']
        axes[2].plot(threshold_labels[:len(widths)], widths, 'bo-', linewidth=2, markersize=8)
        axes[2].axhline(y=final_width, color='r', linestyle='--', label=f'最终宽度={final_width:.1f}')
        axes[2].set_xlabel('阈值百分比')
        axes[2].set_ylabel('宽度(像素)')
        axes[2].set_title('不同阈值下的宽度')
        axes[2].legend()
        axes[2].grid(True, alpha=0.3)

        plt.tight_layout()
        plt.show()

    print(f"精确检测到黑色水平线: 宽度={final_width:.2f}像素, Y坐标={main_peak_idx}")

    return float(final_width), line_contours

#    可视化检测结果
def visualize_detection(image_path, line_contours, save_path=None):
    img = cv2.imread(image_path)
    img_with_contours = img.copy()

    if line_contours:
        # 绘制所有检测到的线轮廓
        for i, line in enumerate(line_contours):
            color = (0, 255, 0) if i == 0 else (255, 0, 0)  # 主要线用绿色，其他用蓝色
            cv2.drawContours(img_with_contours, [line['contour']], -1, color, 2)

            # 标注宽度
            center = (img.shape[1] // 2, int(line['center_y']))
            cv2.putText(img_with_contours,
                        f"W:{line['width']:.1f}",
                        (center[0] - 30, center[1] - 15),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.6, color, 2)

            # 标注严格宽度
            if 'narrow_width' in line:
                cv2.putText(img_with_contours,
                            f"严格:{line['narrow_width']:.1f}",
                            (center[0] - 30, center[1] + 15),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            0.5, (255, 0, 0), 2)

    # 显示结果
    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    plt.title("Original Image")
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    plt.axis('off')

    plt.subplot(1, 2, 2)
    plt.title("Detected Lines")
    plt.imshow(cv2.cvtColor(img_with_contours, cv2.COLOR_BGR2RGB))
    plt.axis('off')

    plt.tight_layout()

    if save_path:
        plt.savefig(save_path, dpi=150, bbox_inches='tight')

    plt.show()
    plt.close()

#    处理目录中的所有激光线图像
def process_images_in_directory(directory_path, output_excel="line_width_results.xlsx", debug_mode=False):
    results = []
    image_extensions = ['.png', '.jpg', '.jpeg', '.tif', '.tiff', '.bmp']

    # 获取目录中的所有图像文件
    image_files = []
    for ext in image_extensions:
        image_files.extend(Path(directory_path).glob(f"*{ext}"))
    image_files = list(image_files)

    print(f"找到 {len(image_files)} 个图像文件")

    # 如果启用调试模式，获取最佳参数
    best_params = None
    if debug_mode and len(image_files) > 0:
        print("\n" + "=" * 50)
        print("高级调试模式: 交互式参数调整")
        print("=" * 50)

        # 使用第一个图像进行调试
        test_image = str(image_files[0])
        print(f"使用图像进行参数调试: {Path(test_image).name}")

        # 启动交互式调试
        best_params, estimated_width = advanced_interactive_debug(test_image)

        print("\n" + "=" * 50)
        print(f"推荐参数:")
        for key, value in best_params.items():
            print(f"  {key}: {value}")
        if estimated_width is not None:
            print(f"估计宽度: {estimated_width:.1f}像素")
        print("=" * 50)

    # 处理每个图像文件
    for i, image_path in enumerate(image_files, 1):
        try:
            print(f"处理文件 {i}/{len(image_files)}: {image_path.name}")

            # 解析文件名
            file_info = parse_filename(image_path.stem)

            # 检测线宽
            if best_params:
                line_width, line_contours = precise_line_width_detection(str(image_path), best_params, debug=(i == 1))
            else:
                line_width, line_contours = precise_line_width_detection(str(image_path), debug=(i == 1))

            # 可视化第一个图像
            if i == 1 and line_contours:
                directory_pathi = "D:\ccd\_result"
                viz_path = Path(directory_pathi) / f"detection_visualization{i}.png"
                visualize_detection(str(image_path), line_contours, str(viz_path))

            # 添加到结果列表
            result_entry = {
                **file_info,
                'line_width_pixels': line_width if line_width else None,
                'line_width_strict': line_contours[0]['narrow_width'] if line_contours and 'narrow_width' in
                                                                         line_contours[0] else None,
                'line_width_fwhm': line_contours[0]['fwhm_width'] if line_contours and 'fwhm_width' in line_contours[
                    0] else None,
                'line_center_y': line_contours[0]['center_y'] if line_contours else None,
                'detection_success': line_width is not None
            }

            results.append(result_entry)

        except Exception as e:
            print(f"处理文件 {image_path.name} 时出错: {str(e)}")
            continue

    # 创建DataFrame
    df = pd.DataFrame(results)

    # 重新排序列顺序
    column_order = ['original_filename', 'x_value', 'y_value', 'date', 'time',
                    'datetime', 'line_width_pixels', 'line_width_strict',
                    'line_width_fwhm', 'line_center_y', 'detection_success']

    # 只包含存在的列
    existing_columns = [col for col in column_order if col in df.columns]
    df = df[existing_columns]

    # 保存到Excel
    directory_path2 = "D:\ccd\_result"
    output_path = Path(directory_path2) / output_excel
    df.to_excel(output_path, index=False)

    print(f"\n处理完成！结果已保存到: {output_path}")
    print(f"成功处理: {df['detection_success'].sum()}/{len(df)} 个文件")

    # 显示统计信息
    if df['line_width_pixels'].notna().any():
        print(f"\n线宽统计:")
        print(f"  平均值: {df['line_width_pixels'].mean():.2f} 像素")
        print(f"  中位数: {df['line_width_pixels'].median():.2f} 像素")
        print(f"  最小值: {df['line_width_pixels'].min():.2f} 像素")
        print(f"  最大值: {df['line_width_pixels'].max():.2f} 像素")
        print(f"  标准差: {df['line_width_pixels'].std():.2f} 像素")

        if 'line_width_strict' in df.columns and df['line_width_strict'].notna().any():
            print(f"\n严格宽度统计:")
            print(f"  平均值: {df['line_width_strict'].mean():.2f} 像素")
            print(f"  中位数: {df['line_width_strict'].median():.2f} 像素")

    return df, output_path

#    处理单个图像文件
def process_single_image(image_path, visualize=True, debug_mode=False):
    print(f"处理单个图像: {image_path}")

    # 如果启用调试模式
    if debug_mode:
        print("\n启动高级交互式调试模式...")
        best_params, estimated_width = advanced_interactive_debug(image_path)
        if best_params:
            print(f"\n使用优化参数进行精确检测...")
            line_width, line_contours = precise_line_width_detection(image_path, best_params, debug=True)
        else:
            line_width, line_contours = precise_line_width_detection(image_path, debug=True)
    else:
        # 解析文件名
        filename = Path(image_path).stem
        file_info = parse_filename(filename)

        print("解析的文件信息:")
        for key, value in file_info.items():
            print(f"  {key}: {value}")

        # 检测线宽
        line_width, line_contours = precise_line_width_detection(image_path, debug=True)

    if line_width is not None:
        print(f"\n检测到的线宽: {line_width:.2f} 像素")

        if line_contours and 'narrow_width' in line_contours[0]:
            print(f"严格宽度: {line_contours[0]['narrow_width']:.2f} 像素")

        # 可视化
        if visualize and line_contours:
            visualize_detection(image_path, line_contours)

        # 创建结果DataFrame
        if not debug_mode:
            result_entry = {
                **file_info,
                'line_width_pixels': line_width,
                'line_width_strict': line_contours[0]['narrow_width'] if line_contours and 'narrow_width' in
                                                                         line_contours[0] else None,
                'line_width_fwhm': line_contours[0]['fwhm_width'] if line_contours and 'fwhm_width' in line_contours[
                    0] else None,
                'detection_success': True
            }

            df = pd.DataFrame([result_entry])

            # 保存到Excel
            output_path = Path(image_path).parent / f"{filename}_results.xlsx"
            df.to_excel(output_path, index=False)
            print(f"\n结果已保存到: {output_path}")

            return df, line_width, line_contours
        else:
            return None, line_width, line_contours
    else:
        print("未检测到黑色水平线")
        return None, None, None


# 使用示例
if __name__ == "__main__":
    plt.rcParams['font.sans-serif'] = ['SimHei', 'DejaVu Sans']
    plt.rcParams['axes.unicode_minus'] = False

    # 分析单张图像的强度剖面
    # image_path = "laser_line_X20_Y2352_20260203_212725.png"
    # widths, peak, profile = analyze_intensity_profile(image_path, debug=True)

    # 处理单个图像（带高级调试模式）

    image_path = "D:\ccd\ccd\screenshots\laser_line_X80_Y2352_20260203_213211.png"
    df, width, contours = process_single_image(image_path, visualize=True, debug_mode=True)


    """
    # 处理整个目录
    directory_path = "D:\ccd\screenshots"
    results_df, output_file = process_images_in_directory(directory_path, debug_mode=True)

    # 显示前几行结果
    if results_df is not None:
        print("\n结果预览:")
        print(results_df.head())
"""
