LN=500000
NC=5

if [ "$1" = "" ]
then
    echo "argument required"
    exit
fi

./build.sh rand-labeling
./build.sh avg
./build.sh relabel

split -l $LN $1 out
ls out* > list
#head -n 20 list > list-20
#./rename.sh list-20
time ./rename.sh list
echo "now initlializing labels ..."
time ./rand-labeling $LN $NC
