COUNTER=0
for line in `cat ${1}`
do
    echo "now processing " $line ":" $COUNTER " ..."
    cp $line $COUNTER
    COUNTER=`expr $COUNTER + 1`
done
