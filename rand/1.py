import sys 
import os

argvs = sys.argv  
argc = len(argvs) 

f = open(argvs[1])
line = f.readline() 

fList = []
while line:
    fList.append(line.strip())
    line = f.readline() 

f.close()
    
#print fList

wList = []
for i in fList:
    
    f = open(i)
    line = f.readline()

    while line:
        tmp = line.split(",")
        wList.append(tmp[0])
        line = f.readline()

    f.close()
        
#print wList
wList_uniq = list(set(wList)) 
print wList_uniq

try:
    os.remove("warnlist")
except:
    pass

# generating list
for i in wList_uniq:
    f = open("warnlist", 'a') 
    if len(i) > 5:
        f.write(str(i) + "\n") 
    f.close()

counter = 0
for i in wList_uniq:
    fname= "fp-" + str(counter)

    try:
        os.remove(fname)
    except:
        pass
    
    counter = counter + 1

fcounter = 0
for j in fList:

    f = open(j)
    line = f.readline() 

    while line:
        #print line.strip() + ":" + str(j)
        tmp = line.split(",")
        
        wcounter = 0 

        flag = 0
        for i in wList_uniq:
            fname= "fp-" + str(wcounter)

            if str(i) == str(tmp[0]):
                print str(i) + "," + str(tmp[1]).strip() + " to " + fname + " at " + str(fcounter)
                f2 = open(fname, 'a') 
                f2.write(tmp[1]) 
                f2.close()
                flag = 1
                
            if flag == 0:
                print "0" + " to " + fname + " at " + str(fcounter)
                f2 = open(fname, 'a') 
                f2.write("0" + "\n") 
                f2.close()

            wcounter = wcounter + 1

        line = f.readline() 

        fcounter = fcounter + 1

    f.close()

