import datetime
import time
from datetime import datetime
import sys 

def datetime_to_epoch(d):
    return int(time.mktime(d.timetuple()))


def epoch_to_datetime(epoch):
    return datetime(*time.localtime(epoch)[:6])

argvs = sys.argv  
argc = len(argvs) 

f = open(argvs[1])
line = f.readline() 

counter = 0
while line:
    tmp = line.split(",")

    d1 = datetime(int(argvs[2]), int(argvs[3]), int(argvs[4]))
    diff = int(tmp[0]) * 60

    epoch = datetime_to_epoch(d1)
    epoch2 = epoch + diff
    d2 = epoch_to_datetime(epoch2)

    f2 = open(argvs[5])
    line2 = f2.readline() 

    while line2:
        tmp2 = line2.split("\t")
        #print(tmp2)
        if str(tmp[1]).strip() == str(tmp2[0]).strip():
            print(str(counter) + "," + str(d2) + "," + str(tmp[1]) + "," + str(tmp2[1]).strip() + "," + str(tmp[2]).strip())
    
        line2 = f2.readline() 

    counter = counter + 1

    f2.close()



    line = f.readline() 
