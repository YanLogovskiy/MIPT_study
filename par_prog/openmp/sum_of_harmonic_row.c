#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

enum Numbers {
	FIX_N = 10,
	N_THREADS = 10
};

//compute row of 1/n, where n from 1 to N

int main(int argc, char** argv) {
	int N, nthreads;
	int i;
	double sum = 0;

	if (argc == 3) {
		N = atoi(argv[1]);
		nthreads = atoi(argv[2]);
	} else {
		N = FIX_N;
		nthreads = N_THREADS;
	}

	omp_set_num_threads(nthreads);

	#pragma omp parallel for reduction(+:sum)
		for (i = 1; i < N; i++) {
			sum += 1.0 / i;
		}

	printf("Sum of 1/n for n from 1 to %d is: %.4lf\n", N, sum);

}
