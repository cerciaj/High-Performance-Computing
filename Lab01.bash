#!/usr/bin/bash
echo $(cat /proc/cpuinfo | grep "model name" -m1)
echo $(cat /proc/meminfo | grep "MemTotal")
echo $(g++ -O3 -Wall --std=c++17 Lab01.cpp -o Lab01)
echo $(python3 cpplint.py Lab01.cpp)
for i in {1..5}
do
	echo $(/usr/bin/time ./Lab01)
done
