#!usr/bin/bash
	echo $(cat /proc/cpuinfo | grep "model name" -m1)
	echo $(cat /proc/meminfo | grep "MemTotal")

	g++ -g -O3 -std=c++17 -Wall Lab05.cpp -o Lab05
	for i in {1..2}
	do
		/usr/bin/time -f"%e %S" ./Lab05
	done
	g++ -g -O3 -std=c++17 -Wall -fopenmp Lab05.cpp -o Lab05_omp
	for i in {1..8}
	do
		export OMP_NUM_THREADS=$i
		for i in {1..2}
		do
			/usr/bin/time -f"%e %S" ./Lab05_omp
		done
	done

