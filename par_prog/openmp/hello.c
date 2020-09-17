#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

enum Numbers {
	PROC_NUM = 10,
};

int main(int argc, char **argv) {
	int def_nthreads, nthreads, tid;

	if (argc > 1) {
		def_nthreads = atoi(argv[1]);
	} else {
		def_nthreads = PROC_NUM;
	}
	omp_set_num_threads(def_nthreads);

	#pragma omp parallel private(nthreads, tid)
	{
		tid = omp_get_thread_num();
		printf("Hello world from thread = %d\n", tid);
		
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
	}
	return 0;
}
