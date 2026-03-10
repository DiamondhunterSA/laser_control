import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# 1. 读取并清理数据
df = pd.read_excel('total.xlsx')
# 过滤掉非正常状态的数据
df_clean = df[df['status'] == 'ok'].copy()

# 2. 设置整体绘图风格
sns.set_theme(style="whitegrid") # 使用带网格的清晰背景
plt.figure(figsize=(18, 5))      # 设置画布大小：宽18，高5，容纳3个子图

# ==========================================
# 子图 1: 速度 (Speed) vs 线宽
# ==========================================
plt.subplot(1, 3, 1)
sns.lineplot(data=df_clean, x='speed_from_X', y='line_width_FWHM_px', 
             marker='o', markersize=8, color='blue', linewidth=2)
plt.title('Speed vs Line Width', fontsize=14, fontweight='bold')
plt.xlabel('Speed (X)', fontsize=12)
plt.ylabel('Line Width FWHM (px)', fontsize=12)

# ==========================================
# 子图 2: 能量/功率 (Power) vs 线宽
# ==========================================
plt.subplot(1, 3, 2)
sns.lineplot(data=df_clean, x='set_power_W_from_P', y='line_width_FWHM_px', 
             marker='s', markersize=8, color='red', linewidth=2)
plt.title('Power vs Line Width', fontsize=14, fontweight='bold')
plt.xlabel('Set Power (W)', fontsize=12)
plt.ylabel('Line Width FWHM (px)', fontsize=12)

# ==========================================
# 子图 3: Z轴高度 (Focus Position) vs 线宽
# ==========================================
plt.subplot(1, 3, 3)
sns.lineplot(data=df_clean, x='Z', y='line_width_FWHM_px', 
             marker='^', markersize=8, color='green', linewidth=2)
plt.title('Z-axis Height vs Line Width', fontsize=14, fontweight='bold')
plt.xlabel('Z (Focus Position: down4, center, up2)', fontsize=12)
plt.ylabel('Line Width FWHM (px)', fontsize=12)

# 3. 自动调整布局并显示
plt.tight_layout()
plt.show()