mport numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.patches as patches
# 读取图片，转化为数组
pictureA = Image.open("D:/picture/A.JPG")
picturea = Image.open("D:/picture/a1.JPG")
number3_pictureA = np.array(pictureA)
number3_picturea0 = np.array(picturea)
number3_picturea=1.2*number3_picturea0+35
# 读取尺寸
heightA, widthA, _ = number3_pictureA.shape
heighta, widtha, _ = number3_picturea.shape
print("图像A的高度和宽度分别是", heightA, widthA)
print("图像a的高度和宽度分别是", heighta, widtha)
# 转化为灰度图
number_pictureA = np.dot(number3_pictureA[..., :3], [0.299, 0.587, 0.114]).astype('uint8')
number_picturea = np.dot(number3_picturea[..., :3], [0.299, 0.587, 0.114]).astype('uint8')
# 使用NCC算法进行图像匹配
max_ncc = -1
max_x, max_y = 0, 0
window_size = (heighta, widtha)
step = 10 # 设置步长为原来的10倍
for y in range(0, heightA - heighta + 1, step):
    print(y)
    for x in range(0, widthA - widtha + 1, step):
        # 求A与a的灰度平均数
        mean_pictureAxy = np.mean(number_pictureA[y:y+heighta,x:x+widtha])
        mean_picturea = np.mean(number_picturea)
        under_A=np.sqrt(np.sum((number_pictureA[y:y+heighta,x:x+widtha]-mean_pictureAxy)**2))
        under_a=np.sqrt(np.sum((number_picturea-mean_picturea)**2))
        #under_A = np.std(number_pictureA[y:y + heighta, x:x + widtha])
        #under_a = np.std(number_picturea)
        up_Aa=np.sum((number_pictureA[y:y+heighta,x:x+widtha]-mean_pictureAxy)*(number_picturea-mean_picturea))
        ncc=up_Aa/(under_a*under_A)
        if ncc > max_ncc:
            max_ncc = ncc
            max_x, max_y = x, y
# 输出匹配结果
print("最佳匹配位置：（%d, %d）" % (max_x, max_y),max_ncc)
# 读取输入图像
image = plt.imread("D:/picture/A.JPG")
# 创建一个副本用于变换
end_picture = image.copy()
# 选定矩形框的位置和大小
x, y, w, h = max_x, max_y, widtha, heighta
# 对矩形区域内的像素进行亮度变换
a1 = end_picture[y:y+h, x:x+w]
a1 = 1.2 * a1 + 35
end_picture[y:y+h, x:x+w] = a1
# 创建一个绘图对象并显示图像
fig, ax = plt.subplots()
# 显示变换后的图像
ax.imshow(end_picture)
# 创建一个矩形框对象
rect = patches.Rectangle((x, y), w, h, linewidth=2, edgecolor='green', facecolor='none')
# 将矩形框添加到绘图对象中
ax.add_patch(rect)
# 显示结果
plt.show()

package main

import "fmt"
