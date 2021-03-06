session = LOAD '$SRCS' USING PigStorage(',') AS (session_id:int,capture_time:chararray,src_and_dest_ip_class:chararray,src_university_id:int,dest_university_id:int,subtype:chararray,generated_time:chararray,source_ip:chararray,src_country_code:chararray,destination_ip:chararray,dest_country_code:chararray,rule_name:chararray,source_user:chararray,destination_user:chararray,application:chararray,virtual_system:chararray,source_zone:chararray,destination_zone:chararray,log_forwarding_profile:chararray,repeat_cnt:int,source_port:int,destination_port:int,flags:chararray,protocol:chararray,action:chararray,bytes:int,bytes_sent:int,bytes_received:int,packets:int,start_time:chararray,elapsed_time:chararray,category:chararray,source_location:chararray,destination_location:chararray,packets_sent:int,packets_received:int,session_end_reason:chararray,action_source:chararray,src_university_name:chararray,dest_university_name:chararray);

--STEP1: tmp-addrpair
addrpair = FOREACH session GENERATE                                    
	   	   session_id as sid,
	   	   destination_ip as destip,
		   source_ip as sourceip,
		   bytes as bytes;

addrpair_distinct = DISTINCT addrpair;
-- dump addrpair_distinct
STORE addrpair_distinct INTO 'tmp-addrpair' USING PigStorage(',');

--STEP2: tmp-addrpair-avg
addrpair_distinct_2 = LOAD 'tmp-addrpair' USING PigStorage(',') AS (destip:chararray, sourceip:chararray, bytes:int);
addrpair_group = GROUP addrpair_distinct_2 BY (destip, sourceip);

addrpair_avg = FOREACH addrpair_group GENERATE
	       	       group as label,
		       AVG(addrpair_distinct_2.bytes),
		       COUNT(sid);
STORE addrpair_avg INTO 'tmp-addrpair-sid' USING PigStorage(',');