#include <omp.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <random>

#define RUNLENGTH 20000000
#define N 100

struct drand48_data state;

double generateNums (double mu, double sigma) {

	static double spare;
	static bool hasSpare = false;

	if (hasSpare) {
		hasSpare = false;
		return spare * sigma + mu;
	} else {
		double u, v, s;
		do {
			drand48_r(&state, &u);
			drand48_r(&state, &v);
			s = u * u + v * v;
		} while (s >= 1.0 || s == 0.0);
		s = sqrt(-2.0 * log(s) / s);
		spare = v * s;
		hasSpare = true;
		return mu + sigma * u * s;
	}
}

void doMarsagila(double *ave, double *stdDev, double mu, double sigma) {
	double sum = 0.0;

	for (int i = 0; i < RUNLENGTH; i++) {
		double num = generateNums(mu, sigma);
		sum += num;
		*ave = sum / 20000000.0;
		*stdDev = sqrt(pow(num - *ave, 2) / 20000000);
	}

}

int main (int argc, char *argv[]) {

	srand48_r(std::stol(argv[1]), &state);
	double mu = 42.0, sigma = 5.0, ave, stdDev;
	for (int i = 0; i < N; i++) {
		doMarsagila(&ave, &stdDev, mu, sigma);
		//std::cout << "Average " << ave << " stdDev " << stdDev << std:: endl;
	}
}
