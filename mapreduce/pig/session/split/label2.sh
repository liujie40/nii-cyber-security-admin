hadoop fs -put addrpair-join-all

hadoop fs -rmr tmp-avg
hadoop fs -rmr tmp-cls-0
hadoop fs -rmr tmp-cls-1
hadoop fs -rmr tmp-cls-2
hadoop fs -rmr tmp-cls-3
hadoop fs -rmr tmp-cls-4

pig -param SRCS=$1 label2.pig

hadoop fs -get tmp-avg
hadoop fs -get tmp-cls-0
hadoop fs -get tmp-cls-1
hadoop fs -get tmp-cls-2
hadoop fs -get tmp-cls-3
hadoop fs -get tmp-cls-4
