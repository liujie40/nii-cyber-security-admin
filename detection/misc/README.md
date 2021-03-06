# maven path - .bashrc

<pre>
alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

alias e='emacs --color=no'

if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

export PATH=$PATH:/root/apache-maven-3.3.9/bin
</pre>

# building maven project

<pre>
mvn archetype:generate \
      -DarchetypeArtifactId=maven-archetype-quickstart \
      -DinteractiveMode=false \
      -DgroupId=com.v4v6 \
      -DartifactId=v6
</pre>

# result: fd00:0:x.x.x.x

<pre>
[INFO] --- exec-maven-plugin:1.5.0:java (default-cli) @ v6 ---
1行目：ABCD:2345:6789:ABCD:EF01:2345:6789,ABCE:EF01:2345:6789:ABCD:EF01:2345:6789
ABCD(43981):2345(9029):6789(26505):ABCD(43981):EF01(61185):2345(9029):6789(26505):SUM:220215
ABCE(43982):EF01(61185):2345(9029):6789(26505):ABCD(43981):EF01(61185):2345(9029):6789(26505):SUM:281401

2行目：ABCD:3345:6789:ABCD:EF01:2345:6789,ABCD:EF01:2345:6789:ABCD:EF01:2345:6789
ABCD(43981):3345(13125):6789(26505):ABCD(43981):EF01(61185):2345(9029):6789(26505):SUM:224311
ABCD(43981):EF01(61185):2345(9029):6789(26505):ABCD(43981):EF01(61185):2345(9029):6789(26505):SUM:281400

3行目：ABCE:4345:6789:ABCD:EF01:2345:6789,ABCF:EF01:2345:6789:ABCD:EF01:2345:6789
ABCE(43982):4345(17221):6789(26505):ABCD(43981):EF01(61185):2345(9029):6789(26505):SUM:228408
ABCF(43983):EF01(61185):2345(9029):6789(26505):ABCD(43981):EF01(61185):2345(9029):6789(26505):SUM:281402

4行目：ABCD:2345:6789:ABCD:EF01:2345:6789,ABCD:EF01:2345:6789:ABCD:EF01:2345:6789
ABCD(43981):2345(9029):6789(26505):ABCD(43981):EF01(61185):2345(9029):6789(26505):SUM:220215
ABCD(43981):EF01(61185):2345(9029):6789(26505):ABCD(43981):EF01(61185):2345(9029):6789(26505):SUM:281400

5行目：251.100.1.1,172.16.0.1
fd00(64768):0:251(593):100(256):1(1):1(1):SUM:65619
fd00(64768):0:172(370):16(22):0(0):1(1):SUM:65161

6行目：251.100.1.2,172.16.0.2
fd00(64768):0:251(593):100(256):1(1):2(2):SUM:65620
fd00(64768):0:172(370):16(22):0(0):2(2):SUM:65162
</pre>

# result: uniq number assignment

<pre>

[INFO] --- exec-maven-plugin:1.5.0:java (default-cli) @ v4v6 ---
1行目：ABCD:2345:6789:ABCD:EF01:2345:6789,ABCE:EF01:2345:6789:ABCD:EF01:2345:6789
2行目：ABCD:3345:6789:ABCD:EF01:2345:6789,ABCD:EF01:2345:6789:ABCD:EF01:2345:6789
3行目：ABCE:4345:6789:ABCD:EF01:2345:6789,ABCF:EF01:2345:6789:ABCD:EF01:2345:6789
4行目：ABCD:2345:6789:ABCD:EF01:2345:6789,ABCD:EF01:2345:6789:ABCD:EF01:2345:6789
5行目：251.100.1.1,172.16.0.1
6行目：251.100.1.2,172.16.0.2
the number of v4 address:4
v4 sum:1086
v4 mean:271.0
the number of v6 address:8
v6 sum:2018752
v6 mean:252344.0
1行目：ABCD:2345:6789:ABCD:EF01:2345:6789,ABCE:EF01:2345:6789:ABCD:EF01:2345:6789
Re: v6 sum:2238967:distance:1986623.0
Re: v6 sum:2520368:distance:2268024.0
2行目：ABCD:3345:6789:ABCD:EF01:2345:6789,ABCD:EF01:2345:6789:ABCD:EF01:2345:6789
Re: v6 sum:2744679:distance:2492335.0
Re: v6 sum:3026079:distance:2773735.0
3行目：ABCE:4345:6789:ABCD:EF01:2345:6789,ABCF:EF01:2345:6789:ABCD:EF01:2345:6789
Re: v6 sum:3254487:distance:3002143.0
Re: v6 sum:3535889:distance:3283545.0
4行目：ABCD:2345:6789:ABCD:EF01:2345:6789,ABCD:EF01:2345:6789:ABCD:EF01:2345:6789
Re: v6 sum:3756104:distance:3503760.0
Re: v6 sum:4037504:distance:3785160.0
5行目：251.100.1.1,172.16.0.1
Re: v4 sum:1439:distance:1168.0
Re: v4 sum:1628:distance:1357.0
6行目：251.100.1.2,172.16.0.2
Re: v4 sum:1982:distance:1711.0
Re: v4 sum:2172:distance:1901.0

</pre>

