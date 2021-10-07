#!/usr/bin/bash

echo $(cat /proc/cpuinfo | grep "model name" -m1)
echo $(cat /proc/meminfo | grep "MemTotal")
echo $(cpplint.py Lab02.cpp)
echo $(g++ -O3 -Wall --std=c++17 Lab02.cpp -o Lab02)
echo "Switch"
for i in {1..8}
do
	echo $(/usr/bin/time -f"%U %S %E" ./Lab02 switch 2000000000)
done
echo "if"
for i in {1..8}
do
	echo $(/usr/bin/time -f"%U %S %E" ./Lab02 if 2000000000)
done
