#include <mpi.h>
#include <stdio.h>

enum
{
    N = 16
};

//we are going to compute sum(1/k), k from 1 to N

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int P, rank; //P - number of processes involved, rank - process id in network group
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &P); //MPI_COMM_WORLD - id of global communcator
    printf("num_of_processes: %d\n", P);

    float num = 0, sum = 0, j = 0;
    int i = 0, el_per_proc = N / P;

    if (rank != 0)
    {
        for(j = ((el_per_proc*rank) + 1); j < (el_per_proc*(rank + 1) + 1); j++)
            sum += 1/j;
        MPI_Send(&sum, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    }
    else //we need proccess with id = 0, because it has access to the console we working with
    {
        for(j = 1; j < el_per_proc + 1; j++)
            sum += 1/j;

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
