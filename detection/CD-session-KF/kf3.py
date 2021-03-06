import sys 
import commands
import numpy as np

import matplotlib.pyplot as plt


def normalize(v, axis=-1, order=2):
    l2 = np.linalg.norm(v, ord = order, axis=axis, keepdims=True)
    l2[l2==0] = 1
    return v/l2

def test(measured):
    max_index = max(xrange(len(measured)), key=lambda i: measured[i])

    split_1 = measured[0:max_index]
    split_2 = measured[max_index+1:-1]

    ## A : [A|B]
    
    f = open('split_1', 'w')
    linecounter = 0
    for i in split_1:
        f.write(str(i) + "\n")
        linecounter = linecounter + 1
    f.close() 
    
    check = commands.getoutput("./main split_1 " + str(linecounter) + " > split_1_filtered")
        #print check

    split_1_KF = []

    f = open('split_1_filtered')
    line = f.readline() 
    while line:
        tmp = line.split(",")
        split_1_KF.append(float(tmp[0]))
        line = f.readline() 
    f.close()

    ## B : [A|B]

    f = open('split_2', 'w')
    linecounter = 0
    for i in split_2:
        f.write(str(i) + "\n")
        linecounter = linecounter + 1
    f.close() 
    
    check = commands.getoutput("./main split_2 " + str(linecounter) + " > split_2_filtered")
        #print check
        
    split_2_KF = []

    f = open('split_2_filtered')
    line = f.readline() 
    while line:
        tmp = line.split(",")
        split_2_KF.append(float(tmp[0]))
        line = f.readline() 
    f.close()
    
    split_KF = split_1_KF +  split_2_KF

    return split_KF
    
argvs = sys.argv  
argc = len(argvs) 

f = open(argvs[1])
line = f.readline() 
measured = []

while line:
    tmp = line.split(",")
    measured.append(float(tmp[0].strip()))
    line = f.readline()

f.close()

KF = measured

num = 0
while num < 200:
      KF = test(KF)
      num += 1

KF2 = KF
      
num = 0
while num < 200:
      KF = test(KF2)
      num += 1

KF3 = KF2
      
num = 0
while num < 200:
      KF3 = test(KF3)
      num += 1
      
plt.subplot(2, 2, 1)
plt.title("measured")
plt.plot(measured)

plt.subplot(2, 2, 2)
plt.title("filtered1")
plt.plot(KF)

plt.subplot(2, 2, 3)
plt.title("filtered2")
plt.plot(KF2)

plt.subplot(2, 2, 4)
plt.title("filtered3")
plt.plot(KF3)

plt.show()  
