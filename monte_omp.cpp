#include <omp.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cmath>


// Copyright 2020 by Alan M. Ferrenberg
// This program is offered freely for any academic use

//  Size of the individual trials of dart throws
#define RUNLENGTH 1000000

using std::stoi;
using std::stoul;
using std::cout;
using std::endl;
using std::setprecision;

// Each thread will have its own copy of the random number state which must
// persist throughout the program.  Make this state be a global variable and
// define it as threadprivate

struct drand48_data state;
#pragma omp threadprivate(state)

// Function to initialize the random number states for each thread.  Each
// thread gets a unique seed based on the single seed provided as an argument
void initRNG(unsigned int seed) {
#pragma omp parallel
  {
    int k = omp_get_thread_num();

    // set the initial seed and state with thread-safe version
    srand48_r(seed+23*k, &state);
  }
  return;
}

// This function uses Monte Carlo integration to estimate pi
double monteCarloIntegration(int N) {
  double pi = 0.0;
  // Fill in this routine with a computation of pi using Monte Carlo
  // integration of a quadrant of a circle.
double in_circle = 0.0;
double x_coor, y_coor;
double dist;

#pragma omp parallel for shared(N) private(x_coor, y_coor, dist) reduction(+:in_circle)
  for(int i = 0; i < N; i++) {
	drand48_r(&state, &x_coor);
	drand48_r(&state, &y_coor);
	dist = sqrt(x_coor * x_coor + y_coor * y_coor);
	if (dist <= 1)
		in_circle++;
  }
  pi = in_circle * 4 / double(N);
  return pi;
}

// Main program
int main(int argc, char* argv[]) {
  // N is the number of random numbers to generate
  int N = stoi(argv[1]);
  // The random number generator seed used to generate the RNG state
  unsigned int seed = stoi(argv[2]);
  // Initialize the random number generator
  initRNG(seed);
  double pi = 0.0;
#pragma omp parallel for shared(N) reduction(+:pi)
  for (int i = 0; i < 1000000; i++) {
	pi += monteCarloIntegration(N);
  }

  pi = pi / 1000000;
  cout << pi << " ";
  return 0;
}
