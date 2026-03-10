import os
import re
import cv2
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from openpyxl import Workbook


def gaussian_func(x, a, mu, sigma, base):
	return a * np.exp(-((x - mu) ** 2) / (2 * sigma ** 2)) + base


def imread_cn(path):
	return cv2.imdecode(np.fromfile(path, dtype=np.uint8), cv2.IMREAD_GRAYSCALE)


def get_first_image(folder):
	exts = (".png", ".jpg", ".jpeg", ".bmp", ".tif", ".tiff")
	files = sorted([f for f in os.listdir(folder) if f.lower().endswith(exts)])
	return os.path.join(folder, files[0]) if files else None


def get_all_images(folder):
	exts = (".png", ".jpg", ".jpeg", ".bmp", ".tif", ".tiff")
	return sorted([f for f in os.listdir(folder) if f.lower().endswith(exts)])


def parse_filename_info(filename_no_ext):
	speed_match = re.search(r"_X([0-9]+(?:\.[0-9]+)?)", filename_no_ext, re.IGNORECASE)
	power_match = re.search(r"_P([0-9]+(?:\.[0-9]+)?)W", filename_no_ext, re.IGNORECASE)

	speed = float(speed_match.group(1)) if speed_match else None
	power_set_w = float(power_match.group(1)) if power_match else None
	return speed, power_set_w


def measure_and_visualize(image_path, roi_coords):
	img = imread_cn(image_path)
	if img is None:
		raise ValueError(f"图片加载失败: {image_path}")

	y1, y2, x1, x2 = roi_coords
	h, w = img.shape[:2]
	if not (0 <= x1 < x2 <= w and 0 <= y1 < y2 <= h):
		raise ValueError(f"ROI 越界: roi={roi_coords}, image_size=({h}, {w})")

	roi = img[y1:y2, x1:x2]

	# 对列求平均，得到垂直方向灰度分布
	profile = np.mean(roi, axis=1)
	x_data = np.arange(len(profile))

	base_guess = np.max(profile)
	a_guess = np.min(profile) - base_guess
	mu_guess = np.argmin(profile)
	sigma_guess = max(2.0, len(profile) / 10.0)

	popt, _ = curve_fit(
		gaussian_func,
		x_data,
		profile,
		p0=[a_guess, mu_guess, sigma_guess, base_guess],
		maxfev=10000,
	)
	a, mu, sigma, base = popt

	fwhm = 2.355 * abs(sigma)

	fit_y = gaussian_func(x_data, a, mu, sigma, base)
	half_level = base + a / 2.0
	left = mu - fwhm / 2.0
	right = mu + fwhm / 2.0

	fig, axes = plt.subplots(1, 2, figsize=(12, 4.8))

	axes[0].imshow(img, cmap="gray")
	rect = plt.Rectangle((x1, y1), x2 - x1, y2 - y1, fill=False, edgecolor="lime", linewidth=2)
	axes[0].add_patch(rect)
	axes[0].set_title("原图与 ROI")
	axes[0].axis("off")

	axes[1].plot(x_data, profile, "b.", label="ROI 平均灰度剖面")
	axes[1].plot(x_data, fit_y, "r-", linewidth=2, label="高斯拟合")
	axes[1].axhline(half_level, color="orange", linestyle="--", linewidth=1.5, label="半高位置")
	axes[1].axvline(left, color="green", linestyle="--", linewidth=1.2)
	axes[1].axvline(right, color="green", linestyle="--", linewidth=1.2)
	axes[1].set_title(f"线宽 FWHM = {fwhm:.3f} px")
	axes[1].set_xlabel("ROI 内相对像素位置 (Y)")
	axes[1].set_ylabel("灰度")
	axes[1].legend(loc="best")
	axes[1].grid(alpha=0.25)

	plt.tight_layout()
	plt.show()

	return fwhm


def measure_line_width(image_path, roi_coords):
	img = imread_cn(image_path)
	if img is None:
		raise ValueError(f"图片加载失败: {image_path}")

	y1, y2, x1, x2 = roi_coords
	h, w = img.shape[:2]
	if not (0 <= x1 < x2 <= w and 0 <= y1 < y2 <= h):
		raise ValueError(f"ROI 越界: roi={roi_coords}, image_size=({h}, {w})")

	roi = img[y1:y2, x1:x2]
	profile = np.mean(roi, axis=1)
	x_data = np.arange(len(profile))

	base_guess = np.max(profile)
	a_guess = np.min(profile) - base_guess
	mu_guess = np.argmin(profile)
	sigma_guess = max(2.0, len(profile) / 10.0)

	popt, _ = curve_fit(
		gaussian_func,
		x_data,
		profile,
		p0=[a_guess, mu_guess, sigma_guess, base_guess],
		maxfev=10000,
	)
	_, _, sigma, _ = popt
	return 2.355 * abs(sigma)


def export_results_to_xlsx(results, output_path):
	wb = Workbook()
	ws = wb.active
	ws.title = "down4_batch_results"

	headers = [
		"file_name",
		"speed_from_X",
		"set_power_W_from_P",
		"actual_power_W(set/21)",
		"actual_power_mW(set/21*1000)",
		"line_width_FWHM_px",
		"status",
		"error",
	]
	ws.append(headers)

	for row in results:
		ws.append([
			row["file_name"],
			row["speed_from_X"],
			row["set_power_W_from_P"],
			row["actual_power_W"],
			row["actual_power_mW"],
			row["line_width_FWHM_px"],
			row["status"],
			row["error"],
		])

	wb.save(output_path)


if __name__ == "__main__":
	script_dir = os.path.dirname(os.path.abspath(__file__))
	med_dir = os.path.join(script_dir, "down4")
	image_files = get_all_images(med_dir)
	if not image_files:
		raise FileNotFoundError(f"未在目录中找到图片: {med_dir}")

	# 请按你的图像实际位置调整 ROI
	roi = [600, 800, 150, 450]  # [y1, y2, x1, x2]

	# 功率换算系数：实际功率 = 标称功率 / 21
	power_scale = 1.0 / 21.0

	# 先对第一张图做一次可视化确认
	first_image_path = os.path.join(med_dir, image_files[0])
	print(f"可视化示例: {image_files[0]}")
	demo_width = measure_and_visualize(first_image_path, roi)
	print(f"示例线宽 FWHM: {demo_width:.4f} px")

	results = []
	print("\n开始批量测量 med 文件夹...")
	for idx, file_name in enumerate(image_files, 1):
		image_path = os.path.join(med_dir, file_name)
		stem = os.path.splitext(file_name)[0]
		speed, power_set_w = parse_filename_info(stem)

		actual_power_w = power_set_w * power_scale if power_set_w is not None else None
		actual_power_mw = actual_power_w * 1000.0 if actual_power_w is not None else None

		row = {
			"file_name": file_name,
			"speed_from_X": speed,
			"set_power_W_from_P": power_set_w,
			"actual_power_W": actual_power_w,
			"actual_power_mW": actual_power_mw,
			"line_width_FWHM_px": None,
			"status": "ok",
			"error": "",
		}

		try:
			row["line_width_FWHM_px"] = measure_line_width(image_path, roi)
			print(
				f"[{idx}/{len(image_files)}] {file_name} | "
				f"speed={speed} | Pset={power_set_w} W | "
				f"Pactual={actual_power_mw:.3f} mW" if actual_power_mw is not None else
				f"[{idx}/{len(image_files)}] {file_name} | speed={speed} | Pset={power_set_w} W | Pactual=None"
			)
		except Exception as e:
			row["status"] = "failed"
			row["error"] = str(e)
			print(f"[{idx}/{len(image_files)}] {file_name} | 失败: {e}")

		results.append(row)

	out_xlsx = os.path.join(script_dir, "down4_linewidth_results.xlsx")
	export_results_to_xlsx(results, out_xlsx)
	print(f"\n批量结果已导出: {out_xlsx}")
