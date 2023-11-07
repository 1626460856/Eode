import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

_x = np.arange(4)
_y = np.arange(3)
_xx, _yy = np.meshgrid(_x, _y)
x, y = _xx.ravel(), _yy.ravel()

# 这是你的 3D 数据
data = [
    [111, 121, 131, 141],
    [211, 221, 231, 241],
    [311, 321, 331, 341]
]

# 将数据转化为 1D 数组
z = np.array(data).ravel()

dx = dy = 0.8 # 宽度
dz = z        # 高度

ax.bar3d(x, y, np.zeros(len(z)), dx, dy, dz)

plt.show()
