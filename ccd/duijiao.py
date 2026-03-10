import sys
import os
import numpy as np
import cv2
import time


# 清晰度评价函数
def calculate_sharpness(image):
    """
    计算图像的清晰度评分
    使用拉普拉斯算子计算图像梯度方差作为清晰度指标
    """
    if image is None or len(image.shape) == 3:
        # 如果是彩色图像，转换为灰度图
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray = image

    # 使用拉普拉斯算子计算图像梯度
    laplacian = cv2.Laplacian(gray, cv2.CV_64F)

    # 计算梯度的方差作为清晰度指标
    sharpness = laplacian.var()

    return sharpness