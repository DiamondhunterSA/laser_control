import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler, PolynomialFeatures
from sklearn.linear_model import Ridge
from sklearn.metrics import mean_squared_error, r2_score, mean_absolute_error

# ==========================================
# 1. 准备工作 (沿用之前步骤)
# ==========================================
df = pd.read_excel('total.xlsx')
df_model = df[df['status'] == 'ok'].copy()

X = df_model[['speed_from_X', 'set_power_W_from_P', 'Z']]
y = df_model['line_width_FWHM_px']

# 特征工程与标准化
poly = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly.fit_transform(X)
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X_poly)

# 划分数据集 (20% 用于测试)
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# 训练 Ridge 模型
ridge_model = Ridge(alpha=1.0)
ridge_model.fit(X_train, y_train)

# ==========================================
# 2. 核心评估代码 (R2, RMSE 等)
# ==========================================

# 对训练集和测试集分别预测
y_train_pred = ridge_model.predict(X_train)
y_test_pred = ridge_model.predict(X_test)

# 计算指标
metrics = {
    "Train R2": r2_score(y_train, y_train_pred),
    "Test R2": r2_score(y_test, y_test_pred),
    "Train RMSE": np.sqrt(mean_squared_error(y_train, y_train_pred)),
    "Test RMSE": np.sqrt(mean_squared_error(y_test, y_test_pred)),
    "Test MAE": mean_absolute_error(y_test, y_test_pred) # 平均绝对误差
}

print("--- 详细模型评估报告 ---")
for k, v in metrics.items():
    print(f"{k:12}: {v:.4f}")

# 3. 交叉验证 (评估模型稳定性)
# 使用 5 折交叉验证，看 R2 的波动
cv_scores = cross_val_score(ridge_model, X_scaled, y, cv=5, scoring='r2')
print(f"\n5-折交叉验证 R2 平均值: {cv_scores.mean():.4f} (+/- {cv_scores.std()*2:.2f})")

# ==========================================
# 4. 可视化分析 (诊断图)
# ==========================================
plt.figure(figsize=(12, 5))

# 图 1：拟合优度图 (Predicted vs Actual)
plt.subplot(1, 2, 1)
plt.scatter(y_test, y_test_pred, color='blue', alpha=0.6, label='Test Data')
plt.plot([y.min(), y.max()], [y.min(), y.max()], 'r--', lw=2, label='Perfect Fit')
plt.xlabel('Actual Line Width (px)')
plt.ylabel('Predicted Line Width (px)')
plt.title(f'Goodness of Fit (R²={metrics["Test R2"]:.3f})')
plt.legend()
plt.grid(True, alpha=0.3)

# 图 2：残差分布图 (Residuals Distribution)
# 残差 = 实际值 - 预测值。如果残差均匀分布在 0 附近，说明模型假设正确。
plt.subplot(1, 2, 2)
residuals = y_test - y_test_pred
sns.histplot(residuals, kde=True, color='green')
plt.axvline(0, color='red', linestyle='--')
plt.xlabel('Prediction Error (px)')
plt.title(f'Residuals Distribution (RMSE={metrics["Test RMSE"]:.3f})')

plt.tight_layout()
plt.show()