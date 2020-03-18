#include <mpi.h>
#include <stdio.h>

# define N 16

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int P, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    float num = 0, sum = 0, j = 0;
    int i = 0, el_per_proc = N / P;

    for(i; i < P; i++)
        if (rank == i)
        {
            for(j = ((el_per_proc*i) + 1); j < (el_per_proc*(i + 1) + 1); j++)
                sum += 1/j;
            if (i != 0)
            MPI_Send(&sum, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
        }

    if (rank == 0)
    { //master
        if (N % P != 0)
            for(j = (el_per_proc*P) + 1; j < N + 1; j++)
                sum += 1/j;

        for(i = 1; i < P; i++)
        {
            MPI_Recv(&num, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += num;
        }
        printf("Result: %f\n", sum);
    }

    MPI_Finalize();
}
