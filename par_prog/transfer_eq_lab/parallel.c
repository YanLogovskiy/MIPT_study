#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

int T, X, K, M;
double **u;
double *sendbuf, *recvbuf;
double dt, dx;

enum
{
    root = 0,
    max_proc_quantity = 16,
};

double  func(double, double);
double  psi(double);
double  phi(double);
void    initValues(int);
void    fill_and_send(int, int);
void    receive_compute_send_cells(int, int, int, int, int);
void    fill_border_values_and_send();
void    gather_and_dump_data(int);
void    free_memory(int);

int main(int argc, char **argv) {

    T = (argc >= 2) ? atoi( argv[1] ) : 10;
    K = (argc >= 3) ? atoi( argv[2] ) : 5;
    X = (argc >= 4) ? atoi( argv[3] ) : 10;
    M = (argc >= 5) ? atoi( argv[4] ) : 5;

    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    initValues(rank);

    if (rank != root) {
        fill_and_send(rank, size);
    }

    if (rank == root) {
        fill_border_values_and_send();
        gather_and_dump_data(size);
    }

    free_memory(rank);

    MPI_Finalize();
    return 0;
}

void fill_border_values_and_send() {

    int k;
    for (k = 0; k < (K - 2); k++) {
        MPI_Barrier(MPI_COMM_WORLD);
        u[k + 1][0] = psi((k + 1) * dt);
        MPI_Send(&(u[k + 1][0]), 1, MPI_DOUBLE, root + 1, 0, MPI_COMM_WORLD);
    }
    u[K - 1][0] = psi((k + 1) * dt);
}

void fill_and_send(int rank, int size) {

    int k, m, m_start, m_finish;
    int num_of_columns_to_fill = (M - 1) / size;

    m_start = num_of_columns_to_fill * (rank - 1) + 1;

    if (rank == size - 1) {
        m_finish = M - 1;
    } else {
        m_finish = num_of_columns_to_fill * rank;
    }

    for (k = 0; k < (K - 1); k++) {
        receive_compute_send_cells(k, rank, size, m_start, m_finish);
    }

    for (k = 1; k < K; k++) {
        for (m = m_start; m <= m_finish; m++) {
            sendbuf[(k - 1) * (M - 1) + m - 1] = u[k][m];
        }
    }

    MPI_Gather(sendbuf, (K - 1) * (M - 1), MPI_DOUBLE, recvbuf, (K - 1) * (M - 1), MPI_DOUBLE, root, MPI_COMM_WORLD);
}

void receive_compute_send_cells(int k, int rank, int size, int m_start, int m_finish) {

    if (k > 0) {
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Recv(&(u[k][m_start - 1]), 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int m;
    for (m = m_start; m <= m_finish; m++) {
        u[k + 1][m] = u[k][m] + dt * (func(k * dt, m * dx) -
                                        (u[k][m] - u[k][m - 1]) / dx);
    }


    if (rank < (size - 1)) {
        MPI_Send(&(u[k + 1][m_finish]), 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
    }
}

void gather_and_dump_data(int size) {

    MPI_Gather(sendbuf, (K - 1) * (M - 1), MPI_DOUBLE, recvbuf, (K - 1) * (M - 1), MPI_DOUBLE, root, MPI_COMM_WORLD);

    int k, m, rank;
    for (rank = 1; rank < size; rank++) {
        for (k = 0; k < K - 1; k++) {
            for (m = 0; m < M - 1; m++) {
                u[k + 1][m + 1] += recvbuf[(K - 1) * (M - 1) * rank + k * (M - 1) + m];
            }
        }
    }

    FILE* data_file = fopen("parallel_data.txt", "wb");

    for (k = 0; k < K; k++) {
        fprintf(data_file, "%d time_step:\t\t", k);
        for (m = 0; m < M; m++) {
            fprintf(data_file, "%.3f\t\t", u[k][m] );
        }
        fprintf(data_file, "\n");
    }

    fclose(data_file);
}

void initValues(int rank) {

    dx = (double) X / M;
    dt = (double) T / K;

    u = (double**) calloc(K, sizeof(double*));
    assert(u);

    int k;
    for (k = 0; k < K; k++) {
        u[k] = (double*) calloc(M, sizeof(double));
        assert(u[k]);
    }

    sendbuf = (double*) calloc((M - 1) * (K - 1), sizeof(double));
    assert(sendbuf);

    if (rank == root) {
        recvbuf = (double*) calloc((M - 1) * (K - 1) * max_proc_quantity, sizeof(double));
        assert(recvbuf);
    }

    int m;
    for (m = 0; m < M; m++) {
        u[0][m] = phi(m * dx);
    }
}

double func(double t, double x) {
    return x * t;
}

double phi(double x) {
    return x * x;
}

double psi(double t) {
    return t * t;
}

void free_memory(int rank) {
    int i;
    for (i = 0; i < K; i++) {
        free(u[i]);
    }

    free(u);
    free(sendbuf);

    if (rank == root) {
        free(recvbuf);
    }
}
