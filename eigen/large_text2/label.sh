hadoop fs -rmr $1
hadoop fs -put $1

pig -param SRCS=$1 label.pig

