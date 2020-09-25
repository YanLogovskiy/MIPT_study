#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

enum Numbers {
	FIX_N = 10,
	N_THREADS = 3
};

//send number N through threads by circle incrementing it

int main(int argc, char** argv) {
	int N, nthreads, curr_thread = -1;
	int i, tid;
	double sum = 0;

	if (argc == 3) {
		N = atoi(argv[1]);
		nthreads = atoi(argv[2]);
	} else {
		N = FIX_N;
		nthreads = N_THREADS;
	}

	omp_lock_t writelock;
	omp_set_num_threads(nthreads);
	omp_init_lock(&writelock);

	#pragma omp parallel shared(N, curr_thread) private(tid)
	{
		tid = omp_get_thread_num();

		if (tid == 0) {
			omp_set_lock(&writelock);
			N += 1;
			curr_thread = tid;
			omp_unset_lock(&writelock);
		} else {
			while (curr_thread < tid - 1) {
				continue;
			}
			omp_set_lock(&writelock);
			printf("thread %d recieved number %d from thread %d\n",
					tid, N, tid - 1);
			N += 1;
			curr_thread = tid;
			omp_unset_lock(&writelock);
		}

		
		if (tid == 0) {
			while (curr_thread < nthreads - 1) {
				continue;
			}
			printf("thread %d revieved number %d from thread %d\n",
					tid, N, nthreads - 1);
		}
	}

	omp_destroy_lock(&writelock);

	return 0;
}

	
