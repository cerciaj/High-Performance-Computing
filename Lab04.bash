#!usr/bin/bash
	echo $(cat /proc/cpuinfo | grep "model name" -m1)
	echo $(cat /proc/meminfo | grep "MemTotal")
	g++ -g -O2 -Wall -std=c++17 unroll.cpp -o unroll
	g++ -g -O2 -Wall -std=c++17 -funroll-loops unroll.cpp -o unroll-with-funroll
	> Lab04-standard.perfstat
	> Lab04-unrolled.perfstat
	> Lab04-standard-with-funroll.perfstat
	echo "unroll standard"
	for i in {1..5}
	do
		perf stat -d -d -d ./unroll standard 2>> Lab04-standard.perfstat
	done
	echo "unroll unrolled"
	for i in {1..5}
	do
		perf stat -d -d -d ./unroll unrolled 2>> Lab04-unrolled.perfstat
	done
	echo "funroll"
	for i in {1..5}
	do
		perf stat -d -d -d ./unroll-with-funroll standard 2>> Lab04-standard-with-funroll.perfstat
	done
