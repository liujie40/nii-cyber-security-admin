\cp c2 c2.org
\cp c2-sorted c2.bak
python fill5.py c2 | tee c3
#python fill7.py c2 | tee c3
./core c3 10 5 500000 5
./cat.sh list2 # generates "all2"
python 0.py all2 | tee nclstr
./avg2.sh all2
python concate.py all2 avg-all2 c3 | tee c2
./sort.pl c2 > c2-sorted

echo "---- processing ... ----"
echo "####" `date +%Y%m%d_%H-%M-%S` "####" >> process
python comp.py c2.bak c2-sorted >> process
echo "## centdoid ##"  >> process
cat c2-sorted >> process
cat process

