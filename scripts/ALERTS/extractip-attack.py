import sys                                                                                                               
import re                                                                                                               
argvs = sys.argv                                                                                                         
argc = len(argvs)                                                                                                       
f = open(argvs[1])                                                                                                      
line = f.readline()                                                                                                     

iplist = []

while line:                                                                                                            
    tmp = line.split(",")                                                                                                
    iplist.append(tmp[8])                                                                                               
    iplist.append(tmp[19])
    line = f.readline()                                                                                                 
f.close()

iplist_uniq = list(set(iplist))

for x in iplist_uniq:
    print(x)
