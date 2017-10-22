import datetime
import time
from datetime import datetime
import sys 

def datetime_to_epoch(d):
    return int(time.mktime(d.timetuple()))


def epoch_to_datetime(epoch):
    return datetime(*time.localtime(epoch)[:6])

#d1 = datetime(2017, 9, 20)
#epoch = datetime_to_epoch(d1)
#print epoch
#epoch2 = epoch + 300
#print epoch_to_datetime(epoch2)

argvs = sys.argv  
argc = len(argvs) 

f = open(argvs[1])
line = f.readline() 

counter = 0
while line:
    #print line.strip()
    tmp = line.split(",")
    #print tmp[0]

    d1 = datetime(int(argvs[2]), int(argvs[3]), int(argvs[4]))
    diff = int(tmp[0]) * 300

    epoch = datetime_to_epoch(d1)
    epoch2 = epoch + diff
    d2 = epoch_to_datetime(epoch2)

    print str(counter) + "," + str(d2) + "," + str(tmp[1]) + "," + str(tmp[2]) + "," + str(tmp[3]).strip()
    
    counter = counter + 1

    line = f.readline() 
