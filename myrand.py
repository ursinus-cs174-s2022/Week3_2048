import numpy as np
import matplotlib.pyplot as plt

RAND_A = 49
RAND_C = 17
RAND_M = 97

def myrand(x):
    ret = RAND_A*x + RAND_C
    fac = np.floor(ret/RAND_M)
    return ret - fac*RAND_M

if __name__ == '__main__':
    xs = [0.1]
    ys = [0.7]
    for i in range(1000):
        xs.append(myrand(xs[-1]))
        ys.append(myrand(ys[-1]))
    xs = np.array(xs)
    ys = np.array(ys)
    plt.subplot(131)
    plt.hist(xs)
    plt.subplot(132)
    plt.hist(ys)
    plt.subplot(133)
    plt.scatter(xs, ys)
    plt.show()
