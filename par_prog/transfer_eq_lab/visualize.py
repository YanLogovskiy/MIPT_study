import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d import Axes3D

with open("parallel_data.txt", "r") as data_file:
    u_matrix = np.array([[float(num) for num in line.split(' ')] for line in data_file])
    
k, m = u_matrix.shape
t_array = np.array(range(0, k))
x_array = np.array(range(0, m))

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

x, t = np.meshgrid(x_array, t_array)

ax.plot_surface(x, t, u_matrix)

ax.set_xlabel('X Label')
ax.set_ylabel('T Label')
ax.set_zlabel('U Label')

plt.show()






