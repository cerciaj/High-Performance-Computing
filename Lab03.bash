#!usr/bin/bash -l

	echo $(cat /proc/cpuinfo | grep "model name" -m1)
	echo $(cat /proc/meminfo | grep "MemTotal")
	g++ -g -O2 -std=c++17 -Wall Lab03-good.cpp -o good
	g++ -g -O2 -std=c++17 -Wall Lab03-bad.cpp -o bad
	perf stat -d -d -d ./good 2> Lab03-good.perfstat
	perf stat -d -d -d ./bad 2> Lab03-bad.perfstat
