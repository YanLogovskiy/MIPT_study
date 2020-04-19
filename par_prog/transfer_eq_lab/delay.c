#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int num_of_proc, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_proc);

    int num = 0;
    double t1, t2;

    t1 = MPI_Wtime();
    if (rank == 0) {
        num += 1;
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Recieved: %d, rank: %d\n", num, rank);
        t2 = MPI_Wtime();
        printf("Delay: %f\n", t2 - t1);
    }
    MPI_Finalize();
}
