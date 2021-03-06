# the number of clusters is hard-coded in *.cpp files.

# data seize: row:nLines, col:nDimensions
nLines=1000000
nDimensions=5

nThreads=700

if [ "$1" = "" ]
then
    echo "argument required: ./first DATA_FILE_NAME"
    exit
fi

rm -rf process
rm -rf process2
rm -rf SSE

echo "STEP1: building executables ..."
./build.sh init-label
./build.sh avg
./build.sh relabel
./build.sh fill2

echo "STEP2: now spliting files ..".
rm -rf hout*
headLine=`expr $nLines \* $nThreads` 
echo "data size:" $headLine 
head -n $headLine $1 > $1.headed

split -l $nLines $1.headed hout

ls hout* > list
time ./rename.sh list # converting hout* to $counter

echo "STEP3: now initlializing labels ..."
time ./init-label $nLines $nDimensions

