#coding:utf-8
# K-means

import numpy as np
import sys
import matplotlib.pyplot as plt

argvs = sys.argv

if __name__ == "__main__":
    data = np.genfromtxt(argvs[1], delimiter=",")
    #print(data)

    #plt.plot(data[:,0])
    #plt.ylim(1)
    plt.subplot(2, 1, 1)
    #plt.title(argvs[1])
    plt.plot(data[:,0])

    plt.subplot(2, 1, 2)
    #plt.title(argvs[2])
    plt.plot(data[:,1])

    plt.tight_layout() 
    plt.show()  
        
    filename = argvs[1] + ".png"
    plt.savefig(filename)

