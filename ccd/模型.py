# -*- coding: utf-8 -*-
"""
激光加工线宽预测模型（基于随机森林）
假设：
1. 图片位于 './laser_lines/' 目录下
2. Excel文件为 './process_parameters.xlsx'，包含列：'image_name', 'speed_x', 'speed_y', 'height_z'
"""
import os
import pandas as pd
import numpy as np
import cv2
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
import warnings
warnings.filterwarnings('ignore')

# -------------------- 第一部分：数据加载与预处理 --------------------
print("=" * 50)
print("步骤1: 加载数据...")

# 1.1 加载工艺参数Excel文件
excel_path = './process_parameters.xlsx'  # 请修改为你的Excel文件路径
df_params = pd.read_excel(excel_path)

# 确保Excel包含必要的列
required_cols = ['image_name', 'speed_x', 'speed_y', 'height_z']
assert all(col in df_params.columns for col in required_cols), f"Excel必须包含列：{required_cols}"
print(f"成功加载工艺参数表，共 {len(df_params)} 条记录。")
print(df_params.head())

# 1.2 定义图像处理函数：从单张图片中提取平均线宽
def measure_line_width(image_path):
    """
    使用OpenCV图像处理技术测量激光线的平均宽度（单位：像素）。
    核心步骤：灰度化 -> 阈值化（二值化）-> 形态学操作 -> 轮廓查找 -> 宽度计算。
    """
    try:
        # 读取图像
        img = cv2.imread(image_path)
        if img is None:
            print(f"警告：无法读取图像 {image_path}")
            return None

        # 转换为灰度图
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # 二值化（阈值可根据你的图像调整，这里假设线条比背景亮）
        _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

        # 形态学操作（可选，用于去除小噪声、连接断线）
        kernel = np.ones((3, 3), np.uint8)
        binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel)

        # 查找轮廓
        contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        if not contours:
            print(f"警告：在 {image_path} 中未检测到轮廓。")
            return None

        # 假设最长的轮廓是我们的激光线
        main_contour = max(contours, key=cv2.contourArea)

        # 计算该轮廓的最小外接矩形，其宽度即为线宽（像素）
        rect = cv2.minAreaRect(main_contour)
        width_pixel = min(rect[1])  # rect[1]为 (宽度, 高度)，取较小值作为线宽

        return width_pixel
    except Exception as e:
        print(f"处理图像 {image_path} 时发生错误: {e}")
        return None

# 1.3 遍历所有图片，测量线宽，并与Excel数据合并
image_dir = './laser_lines/'  # 请修改为你的图片文件夹路径
image_widths = []
valid_indices = []

print(f"\n步骤2: 正在处理图像目录 '{image_dir}' ...")

for idx, row in df_params.iterrows():
    img_name = row['image_name']
    # 确保图片文件名包含扩展名（如 .jpg, .png）
    if not os.path.splitext(img_name)[1]:
        img_name += '.jpg'  # 默认扩展名，请根据你的实际情况修改

    img_path = os.path.join(image_dir, img_name)

    if not os.path.exists(img_path):
        print(f"警告：图片文件不存在，跳过 {img_path}")
        image_widths.append(np.nan)
        continue

    width = measure_line_width(img_path)
    if width is not None:
        image_widths.append(width)
        valid_indices.append(idx)
    else:
        image_widths.append(np.nan)

# 将测量结果添加到DataFrame
df_params['line_width_pixel'] = image_widths

# 清除任何测量失败的记录（包含NaN的行）
df_clean = df_params.dropna(subset=['line_width_pixel']).copy()
print(f"\n有效数据记录数: {len(df_clean)} / {len(df_params)}")

if len(df_clean) < 10:
    print("错误：有效数据过少，无法进行可靠建模。请检查图像和测量函数。")
    exit()

# -------------------- 第二部分：准备机器学习数据 --------------------
print("\n步骤3: 准备训练数据...")

# 特征：工艺参数
X = df_clean[['speed_x', 'speed_y', 'height_z']]
# 目标：线宽（像素）
y = df_clean['line_width_pixel']

print(f"特征形状: {X.shape}, 目标形状: {y.shape}")
print("\n特征描述（统计）:")
print(X.describe())
print("\n目标描述（线宽，像素）:")
print(f"  平均值: {y.mean():.2f}, 标准差: {y.std():.2f}")
print(f"  最小值: {y.min():.2f}, 最大值: {y.max():.2f}")

# 划分训练集和测试集（80%训练，20%测试）
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
print(f"\n数据划分完成 -> 训练集: {X_train.shape[0]} 条, 测试集: {X_test.shape[0]} 条")

# -------------------- 第三部分：训练随机森林模型 --------------------
print("\n" + "=" * 50)
print("步骤4: 训练随机森林回归模型...")

# 创建模型（初始参数可调）
rf_model = RandomForestRegressor(
    n_estimators=100,      # 树的数量
    max_depth=10,          # 树的最大深度，防止过拟合
    min_samples_split=5,   # 内部节点再划分所需最小样本数
    min_samples_leaf=2,    # 叶子节点最少样本数
    random_state=42,
    n_jobs=-1              # 使用所有CPU核心
)

# 训练模型
rf_model.fit(X_train, y_train)
print("模型训练完成！")

# -------------------- 第四部分：模型评估与可视化 --------------------
print("\n步骤5: 模型评估...")

# 在训练集和测试集上进行预测
y_train_pred = rf_model.predict(X_train)
y_test_pred = rf_model.predict(X_test)

# 计算关键评估指标
def print_metrics(y_true, y_pred, dataset_name):
    mae = mean_absolute_error(y_true, y_pred)
    mse = mean_squared_error(y_true, y_pred)
    rmse = np.sqrt(mse)
    r2 = r2_score(y_true, y_pred)
    print(f"\n【{dataset_name}集】")
    print(f"  平均绝对误差 (MAE): {mae:.3f} 像素")
    print(f"  均方根误差 (RMSE): {rmse:.3f} 像素")
    print(f"  决定系数 (R² Score): {r2:.3f}")
    return mae, rmse, r2

print_metrics(y_train, y_train_pred, "训练")
mae_test, rmse_test, r2_test = print_metrics(y_test, y_test_pred, "测试")

# 5.1 可视化：预测值 vs 真实值
plt.figure(figsize=(15, 5))

# 子图1：测试集预测 vs 真实
plt.subplot(1, 3, 1)
plt.scatter(y_test, y_test_pred, alpha=0.6, edgecolors='k')
plt.plot([y.min(), y.max()], [y.min(), y.max()], 'r--', lw=2, label='理想拟合线')
plt.xlabel('真实线宽 (像素)')
plt.ylabel('预测线宽 (像素)')
plt.title(f'测试集: 预测 vs 真实 (R² = {r2_test:.3f})')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)

# 5.2 可视化：特征重要性（这是随机森林的核心输出！）
plt.subplot(1, 3, 2)
importances = rf_model.feature_importances_
feature_names = X.columns
indices = np.argsort(importances)[::-1]  # 降序排列

plt.bar(range(len(importances)), importances[indices], align='center', color='skyblue')
plt.xticks(range(len(importances)), [feature_names[i] for i in indices], rotation=45)
plt.xlabel('工艺参数')
plt.ylabel('重要性分数')
plt.title('特征重要性 (数值越大越重要)')
plt.grid(True, axis='y', linestyle='--', alpha=0.7)

# 在柱子上方添加数值标签
for i, v in enumerate(importances[indices]):
    plt.text(i, v + 0.005, f'{v:.3f}', ha='center', fontsize=9)

# 5.3 可视化：单个特征与线宽的关系（以最重要的特征为例）
top_feature = feature_names[indices[0]]
plt.subplot(1, 3, 3)
plt.scatter(df_clean[top_feature], df_clean['line_width_pixel'], alpha=0.6)
plt.xlabel(top_feature)
plt.ylabel('线宽 (像素)')
plt.title(f'线宽 vs {top_feature}')
plt.grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.show()

# -------------------- 第五部分：模型应用与解读 --------------------
print("\n" + "=" * 50)
print("步骤6: 模型解读与应用示例")

# 6.1 解读特征重要性
print("\n1. 特征重要性解读:")
for i, idx in enumerate(indices):
    print(f"  第{i+1}重要的参数: '{feature_names[idx]}' (重要性: {importances[idx]:.3f})")

# 6.2 使用模型进行新工艺参数的预测
print("\n2. 预测示例:")
# 假设一组新工艺参数 [speed_x, speed_y, height_z]
new_parameters = pd.DataFrame({
    'speed_x': [10.0, 20.0],
    'speed_y': [0.5, 0.8],
    'height_z': [1.0, 1.2]
})
predicted_widths = rf_model.predict(new_parameters)
print("  输入新参数:")
print(new_parameters)
print("  预测线宽 (像素):")
for i, width in enumerate(predicted_widths):
    print(f"    参数组 {i+1}: {width:.2f} 像素")

# 6.3 保存模型供后续使用（可选）
import joblib
model_save_path = './laser_linewidth_rf_model.pkl'
joblib.dump(rf_model, model_save_path)
print(f"\n3. 模型已保存至 '{model_save_path}'，可用于后续预测。")

print("\n" + "=" * 50)
print("代码执行完毕！")
print("关键结论：")
print(f"1. 模型在测试集上的预测误差约为 ±{rmse_test:.2f} 像素。")
print(f"2. 最重要的工艺参数是 '{feature_names[indices[0]]}'。")
print("3. 可通过调整特征重要性高的参数来精确控制线宽。")