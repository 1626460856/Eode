import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.patches as patches

# 读取图片，转化为数组
pictureA = Image.open("D:/picture/A.JPG")
picturea = Image.open("D:/picture/a1.JPG")
number3_pictureA = np.array(pictureA)
number3_picturea = np.array(picturea)
# 读取尺寸
heightA, widthA, _ = number3_pictureA.shape
heighta, widtha, _ = number3_picturea.shape
print("图像A的高度和宽度分别是", heightA, widthA)
print("图像a的高度和宽度分别是", heighta, widtha)
# 转化为灰度图
number_pictureA = np.dot(number3_pictureA[..., :3], [0.299, 0.587, 0.114]).astype('uint8')
number_picturea = np.dot(number3_picturea[..., :3], [0.299, 0.587, 0.114]).astype('uint8')
min_mad = float('inf')  # 初始化为无穷大
best_x = 0
best_y = 0
mad=0
step = 10  # 设置步长为原来的10倍
#for y in range(1200,heightA-heighta+1):
for y in range(0,heightA-heighta+1,step):
    print(y)
    for x in range(0,widthA-widtha+1,step):

        mad = np.mean(np.abs(number_pictureA[y:y + heighta, x:x + widtha] - number_picturea))
        if mad<min_mad:
            min_mad=mad
            best_y=y
            best_x=x
            print(min_mad)

print(min_mad,best_x,best_y)
image = plt.imread("D:/picture/A.JPG")
# 创建一个绘图对象并显示图像
fig, ax = plt.subplots()
ax.imshow(image)
# 选定矩形框的位置和大小
x, y, w, h = best_x, best_y, widtha, heighta
# 创建一个矩形框对象
rect = patches.Rectangle((x, y), w, h, linewidth=2, edgecolor='green', facecolor='none')
# 将矩形框添加到绘图对象中
ax.add_patch(rect)
# 显示结果
plt.show()
