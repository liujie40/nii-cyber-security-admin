if [ "$1" = "" ]
then
    echo "no argument: ./mail.sh startDate endDate"
fi

# ./apt.sh 20180417 20180421

COUNT=$1

rm -rf tmp-list
touch tmp-list

while [ $COUNT -le $2 ]; do
    ./listup.pl | grep detailed | grep -v "iplist/" | grep -v system_tags | grep $COUNT >> tmp-list
    COUNT=`expr $COUNT + 1` # COUNT をインクリメント
done

#cat tmp-list

rm -rf tags-$1-$2
touch tags-$1-$2

rm -rf tmp-tag-tor
touch tmp-tag-tor

COUNT=0
COUNT2=0
while read line; do
    #echo $line
    if [ `echo $line | grep 'delta'` ] ; then
	d=`echo $line | cut -d "-" -f 3`
    else
	d=`echo $line | cut -d "-" -f 4`
    fi
    gr=`python readjson.py $line $d | grep "Tor"`
    echo $gr

    if [ -n "$gr" ]; then
	echo " " 

	if [ `echo $line | grep 'delta'` ] ; then
	    echo " " | tee -a tmp-tag-tor
	    echo $line | sed -e 's/[^0-9]//g' | cut -c 1-8 | tee -a tmp-tag-tor
	    dfn=`echo $line | cut -d "/" -f 3`
	    fn="./delta/"${dfn}
	    echo $fn
	    python readjson2.py ${fn} "Tor" | tee -a tmp-tag-tor
	    COUNT2=`expr $COUNT2 + 1` # COUNT をインクリメント
	else
	    echo " " | tee -a tmp-tag-tor
	    echo $line | sed -e 's/[^0-9]//g' | cut -c 3-10 | tee -a tmp-tag-tor
	    python readjson2.py $line "Tor" | tee -a tmp-tag-tor
	    COUNT2=`expr $COUNT2 + 1` # COUNT をインクリメント
	fi

    fi

    COUNT=`expr $COUNT + 1` # COUNT をインクリメント
done < tmp-list

rm -rf mail-Tor-$1-$2
  
cat tmp-tag-tor > mail-Tor-$1-$2

echo "############"
cat tmp-tag-tor

echo $COUNT2" days" | tee -a mail-Tor-$1-$2

ntag=`grep "\[" tmp-tag-tor | wc -l`
echo $ntag "tags"

grep -E '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' tmp-tag-tor >> mail-Tor-$1-$2
gr=`grep -E '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' tmp-tag-tor | wc -l | tee -a mail-Tor-$1-$2`
#echo $gr " IP addresses"

grep -E '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' tmp-tag-tor > tmp-ipaddress-cc-$1-$2
./drem.pl tmp-ipaddress-tor-$1-$2 > tmp-ipaddress-tor-$1-$2-drem

nIP=`wc -l tmp-ipaddress-tor-$1-$2-drem | cut -d " " -f 1`
echo $nIP" addresses"
cat tmp-ipaddress-tor-$1-$2-drem

#cat tags-$1-$2
#./drem.pl tags-$1-$2 > tags-$1-$2-drem
#cat tags-$1-$2-drem
