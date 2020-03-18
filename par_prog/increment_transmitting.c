#include <mpi.h>
#include <stdio.h>

# define n 4

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Rank: %d\n", rank);
    int num = 0, i = 1;

    if (rank == 0)
    {
        num+=1;
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        for(i; i <= n; i++)
        {
            if (rank == i)
            {
                MPI_Recv(&num, 1, MPI_INT, i-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Recieved: %d, rank: %d\n", num, rank);
                num+=1;
                if (rank != (n - 1))
                    MPI_Send(&num, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
            }
        }
    }
    MPI_Finalize();
}
