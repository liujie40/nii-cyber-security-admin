#extracting unique address pair

<pre>

# ls *csv > csvlist
# ./copyFromLocal.sh csvlist
# ./do.sh csvlist
</pre>

concatenating all files.

<pre>
# python cat.py csvlist 
# wc -l all

# hadoop fs -copyFromLocal all

# time ./addrpair.sh 

real    0m26.088s
user    0m31.788s
sys     0m2.296s

# hadoop fs -copyToLocal all.dump

# wc -l all.dump/*                                                                  
    0 all.dump/_SUCCESS
  968 all.dump/part-r-00000
  968 合計

</pre>

<pre>
 2015  ./pair-count-2.sh alarm-1000 > tmp
 2016  python pair-count-2.py tmp > tmp2
</pre>

<pre>
 2032  time ./pair-count-2.sh target-1000 > tmp
 2034  python pair-count-5.py alarm-1000 tmp
</pre>  