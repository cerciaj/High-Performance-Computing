#include <omp.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <random>

#define RUNLENGTH 20000000
#define N 100

struct drand48_data state;

double generateBoxNums (double mu, double sigma) {

	const double eps = std::numeric_limits<double>::min();
	const double two_pi = 2.0 * M_PI;

	double u1, u2;

	do {
		drand48_r(&state, &u1);
		drand48_r(&state, &u2);
	}
	while (u1 <= eps);
	double z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	return z0 * sigma + mu;
}

void doBoxMuller(double *ave, double *stdDev, double mu, double sigma) {
	double sum = 0.0;

	for (int i = 0; i < RUNLENGTH; i++) {
		double num = generateBoxNums(mu, sigma);
		sum += num;
		*ave = sum / 20000000.0;
		*stdDev = sqrt(pow(num - *ave, 2) / 20000000);
	}

}

int main (int argc, char *argv[]) {

	srand48_r(std::stol(argv[1]), &state);
	double mu = 42.0, sigma = 5.0, ave, stdDev;
	for (int i = 0; i < N; i++) {
		doBoxMuller(&ave, &stdDev, mu, sigma);
		//std::cout << "Average " << ave << " stdDev " << stdDev << std:: endl;
	}
}
