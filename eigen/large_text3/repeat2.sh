\cp c2-sorted c2.bak
#python fill5.py c2 | tee c3
python fill7.py c2 | tee c3
./core c3 10 5 500000 5
./cat.sh list2 # generates "all2"
python 0.py all2 | tee nclstr
./avg2.sh all2
python concate2.py all2 avg-all2 c3 | tee c2
./sort.pl c2 > c2-sorted

python comp.py c2.bak c2-sorted >> process
echo "####" `date +%Y%m%d_%H-%M-%S` "####" >> process
cat process

#python file.py c4 c3 > c2
#python 1.py all2 nclstr.bak 
#cat SSE
#\cp nclstr nclstr.bak
