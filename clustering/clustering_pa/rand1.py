# coding: UTF-8

import numpy as np
import matplotlib.pyplot as plt

rng = np.random.RandomState(123)

d = 2
N = 1000 

mean = 5

x1 = rng.randn(N, d) + np.array([0, 0])
x2 = rng.randn(N, d) + np.array([mean, mean])
x = np.concatenate((x1, x2), axis=0)

#print x1
#print x2

for i in x1:
    constr = ""
    for j in i:
        constr = constr + str(j) + ","
    print constr.rstrip(",")

for i in x2:
    constr = ""
    for j in i:
        constr = constr + str(j) + ","
    print constr.rstrip(",")

#plt.plot(x1, "o")
#plt.plot(x, "o")
#plt.show()

