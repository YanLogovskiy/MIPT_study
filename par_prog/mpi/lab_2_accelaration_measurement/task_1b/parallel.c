#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <string.h>

enum Num {
	ISIZE = 1000,
	JSIZE = 1000,
	IN = 3,
	JN = 4
};

int main(int argc, char** argv) {
	double a[ISIZE][JSIZE];

	double start_time, end_time;
	int rank, size, i, j;

	for (i = 0; i < ISIZE; i++) {
		for (j = 0; j < JSIZE; j++) {
			a[i][j] = 10 * i + j;
		}
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	start_time = MPI_Wtime();

	if (size == 1) {
		for (i = 0; i < ISIZE - IN; i++) {
			for (j = JN; j < JSIZE; j++) {
				a[i][j] = sin(0.00001 * a[i + IN][j - JN]);
			}
		}
	} else {
		int divN = (int) ( (JSIZE - JN) / size);
		int modN = (JSIZE - JN) % size;

		int start = rank * divN;
		int end = (rank + 1) * divN;
		if (rank == size - 1) {
			end += modN;
		}

		double* sendbuf = (double*) malloc((end - start) * sizeof(double));

		//distance vector (-IN, +JN) -> direction vector (>, <)
		//anti dependence -> can parallel by using barrier synchro
		
		for (int i = 0; i < ISIZE - IN; i++) {
			for(int j = start + JN; j < end + JN; j++) {
				sendbuf[j - start - JN] = sin(0.00001 * a[i + IN][j - JN]);
			}
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Allgather(sendbuf, end - start, MPI_DOUBLE, &a[i][JN], end - start, MPI_DOUBLE, MPI_COMM_WORLD);
		}	
	}

	if (rank == 0) {
		end_time = MPI_Wtime();
		printf("size %d, time %f\n", size, end_time - start_time);
		FILE* file = fopen("result.parallel.txt", "w");	
		for (i = 0; i < ISIZE; i++) {
			for (j = 0; j < JSIZE; j++) {
				fprintf(file, "%f ", a[i][j]);
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}

	MPI_Finalize();

	return 0;
}


