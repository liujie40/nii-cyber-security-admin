# cluster size
nClusters=2
nDimensions=6
nThreads=1

# nItems=4 # nDimensions-2 / items: src dst n[* * * *]
nItems=6

nLines=`wc -l 0 | cut -d " " -f 1` 
echo $nLines

echo "STEP: init label..." 

cat count.cpp | sed "s/#define THREAD_NUM N/#define THREAD_NUM $nThreads/" > count.tmp.cpp
cat count.tmp.cpp | sed "s/#define CLUSTER_NUM N/#define CLUSTER_NUM $nClusters/" > count.tmp.2.cpp
cat count.tmp.2.cpp | sed "s/res.rightCols(N)/res.rightCols($nDimensions)/" > count.re.cpp
./build.sh count.re

echo "counting points per cluster..."
time ./count.re $nLines 1 | tee tmp-all-labeled 
sleep 3s

echo "STEP: calculating centroid..." # input; 0, 0.lbl

cat avg.cpp | sed "s/#define THREAD_NUM N/#define THREAD_NUM $nThreads/" > avg.tmp.cpp
cat avg.tmp.cpp | sed "s/#define CLUSTER_NUM N/#define CLUSTER_NUM $nClusters/" > avg.tmp.2.cpp
cat avg.tmp.2.cpp | sed "s/#define ITEM_NUM N/#define ITEM_NUM $nItems/" > avg.tmp.3.cpp
cat avg.tmp.3.cpp | sed "s/rightCols(N)/rightCols($nDimensions)/" > avg.re.cpp
./build.sh avg.re

rm -rf centroid
time ./avg.re $nLines $nDimensions #yields centroid

echo "STEP: relabeling ..."

cat relabel.cpp | sed "s/#define THREAD_NUM N/#define THREAD_NUM $nThreads/" > relabel.tmp.cpp
cat relabel.tmp.cpp | sed "s/#define CLUSTER_NUM N/#define CLUSTER_NUM $nClusters/" > relabel.tmp.2.cpp
cat relabel.tmp.2.cpp | sed "s/rightCols(N)/rightCols($nDimensions)/" > relabel.re.cpp
./build.sh relabel.re
time ./relabel.re centroid $nClusters $nItems $nLines $nDimensions  

\cp 0.rlbl 0.lbl
