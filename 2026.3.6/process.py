import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, PolynomialFeatures
from sklearn.linear_model import Ridge
from sklearn.metrics import mean_squared_error, r2_score
from scipy.optimize import minimize

# ==========================================
# 1. 数据加载与基础预处理
# ==========================================
df = pd.read_excel('total.xlsx')

# 只选取状态正常的数据进行建模
df_model = df[df['status'] == 'ok'].copy()

# 定义输入特征和目标值
# 注意：我们将原始特征输入，后续通过 Pipeline 或手动转换生成平方项和交互项
base_features = ['speed_from_X', 'set_power_W_from_P', 'Z']
target = 'line_width_FWHM_px'

X = df_model[base_features]
y = df_model[target]

# ==========================================
# 2. 特征工程与标准化 (Step 1 & 2)
# ==========================================
# 生成二阶多项式特征 (包含 Speed^2, Power^2, Z^2, 以及各变量间的交互项)
poly = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly.fit_transform(X)

# 归一化：这对正则化模型至关重要，确保不同量级的特征对模型贡献公平
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X_poly)

# ==========================================
# 3. 建立带正则化的模型 (Step 3 & 4)
# ==========================================
# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# 使用岭回归 (Ridge) 引入 L2 正则化，alpha 越大，抗过拟合能力越强
ridge_model = Ridge(alpha=1.0) 
ridge_model.fit(X_train, y_train)

# 评估
y_pred = ridge_model.predict(X_test)
rmse = np.sqrt(mean_squared_error(y_test, y_pred))
r2 = r2_score(y_test, y_pred)

print("--- 模型评估结果 ---")
print(f"均方根误差 (RMSE): {rmse:.4f} px")
print(f"决定系数 (R2 Score): {r2:.4f}")

# ==========================================
# 4. 逆向参数推导函数 (Inverse Optimization)
# ==========================================
def predict_width(s, p, z):
    """辅助函数：输入原始参数，输出模型预测的线宽"""
    features_orig = np.array([[s, p, z]])
    features_poly = poly.transform(features_orig)
    features_scaled = scaler.transform(features_poly)
    return ridge_model.predict(features_scaled)[0]

def find_best_params(target_w, initial_guess=[80, 0.06, 0]):
    """利用数值优化寻找最接近目标线宽的参数组合"""
    def objective(params):
        s, p, z = params
        pred_w = predict_width(s, p, z)
        # 目标是最小化预测值与目标值的平方差
        return (pred_w - target_w)**2
    
    # 设定参数搜索边界 (参考数据集范围)
    bounds = [
        (df_model['speed_from_X'].min(), df_model['speed_from_X'].max()),
        (df_model['set_power_W_from_P'].min(), df_model['set_power_W_from_P'].max()),
        (df_model['Z'].min(), df_model['Z'].max())
    ]
    
    res = minimize(objective, x0=initial_guess, bounds=bounds, method='L-BFGS-B')
    return res.x, predict_width(*res.x)

# 示例：反推目标线宽为 25px 的参数
target_width = 25.0
best_params, final_pred = find_best_params(target_width)

print(f"\n--- 逆向推导示例 (目标线宽: {target_width}px) ---")
print(f"推荐速度 (Speed): {best_params[0]:.2f}")
print(f"推荐功率 (Power): {best_params[1]:.4f} W")
print(f"推荐焦距 (Z): {best_params[2]:.2f}")
print(f"模型在该参数下的预测值: {final_pred:.4f} px")

# ==========================================
# 5. 可视化评估
# ==========================================
plt.figure(figsize=(8, 6))
plt.scatter(y_test, y_pred, alpha=0.7, edgecolors='k')
plt.plot([y.min(), y.max()], [y.min(), y.max()], 'r--', lw=2)
plt.xlabel('Actual Line Width (px)')
plt.ylabel('Predicted Line Width (px)')
plt.title('Actual vs Predicted (Ridge Regression)')
plt.grid(True, linestyle=':', alpha=0.6)
plt.show()