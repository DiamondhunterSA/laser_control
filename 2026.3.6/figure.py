import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler, PolynomialFeatures
from sklearn.linear_model import Ridge

# 1. 重新训练最优模型 (不带手动 P/S 项，R2 ~ 0.75)
df = pd.read_excel('total.xlsx')
df_model = df[df['status'] == 'ok'].copy()

features = ['speed_from_X', 'set_power_W_from_P', 'Z']
X = df_model[features]
y = df_model['line_width_FWHM_px']

poly = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly.fit_transform(X)
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X_poly)

model = Ridge(alpha=1.0)
model.fit(X_scaled, y)

# 2. 准备绘图网格
z_values = [-4, 0, 2] # 对应 down4, center, up2
s_range = np.linspace(X['speed_from_X'].min(), X['speed_from_X'].max(), 100)
p_range = np.linspace(X['set_power_W_from_P'].min(), X['set_power_W_from_P'].max(), 100)
S, P = np.meshgrid(s_range, p_range)

# 3. 创建多子图
fig, axes = plt.subplots(1, 3, figsize=(18, 5), sharex=True, sharey=True)

for i, z in enumerate(z_values):
    # 构造预测矩阵
    Z_val = np.full(S.shape, z)
    grid_points = np.c_[S.ravel(), P.ravel(), Z_val.ravel()]
    
    # 转换与预测
    grid_poly = poly.transform(grid_points)
    grid_scaled = scaler.transform(grid_poly)
    W_pred = model.predict(grid_scaled).reshape(S.shape)
    
    # 绘制填充等值线
    ax = axes[i]
    cp = ax.contourf(S, P, W_pred, levels=15, cmap='Spectral_r')
    
    # 绘制特定的目标线宽参考线 (如 25px, 28px)
    ct = ax.contour(S, P, W_pred, levels=[24, 26, 28, 30], colors='black', linestyles='--', linewidths=0.8)
    ax.clabel(ct, inline=True, fontsize=10, fmt='%1.0f px')
    
    ax.set_title(f'Focus Position Z = {z}')
    ax.set_xlabel('Speed (X)')
    if i == 0: ax.set_ylabel('Power (W)')

# 添加公共颜色条
fig.subplots_adjust(right=0.9)
cbar_ax = fig.add_axes([0.92, 0.15, 0.015, 0.7])
fig.colorbar(cp, cax=cbar_ax, label='Predicted Line Width (px)')

plt.suptitle('Comparison of Process Windows at Different Focus Positions', fontsize=16)
plt.show()