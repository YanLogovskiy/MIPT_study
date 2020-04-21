#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

int T, X, K, M;
double **u;
double dt, dx;

double  func(double t, double x);
double  psi(double t);
double  phi(double x);
void    fill_init_conditions();
void    fill_u_matrix(int rank, int size);
void    fill_border_conditions(int k);
void    compute_u_cells(int k, int rank, int size);
void    dump_data();
void    free_memory();

int main(int argc, char **argv) {

    T = (argc >= 2) ? atoi( argv[1] ) : 10;
    K = (argc >= 3) ? atoi( argv[2] ) : 5;
    X = (argc >= 4) ? atoi( argv[3] ) : 10;
    M = (argc >= 5) ? atoi( argv[4] ) : 5;

    fill_init_conditions();

    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    fill_u_matrix(rank, size);

    if (rank == 0) {
        dump_data();
        free_memory();
    }
    MPI_Finalize();
    return 0;
}

void fill_u_matrix(int rank, int size) {

    int k;
    for (k = 0; k < (K - 1); k++) {
        if (rank == 0) {
            fill_border_conditions(k);
        } else {
            compute_u_cells(k, rank, size);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

void fill_border_conditions(int k) {

    u[k + 1][0] = psi((k + 1) * dt);

}

void compute_u_cells(int k, int rank, int size) {

    int m, m_start, m_finish;
    int num_of_columns_to_fill = (M - 1) / size;

    m_start = num_of_columns_to_fill * (rank - 1) + 1;

    if (rank == size - 1) {
        m_finish = M - 1;
    } else {
        m_finish = num_of_columns_to_fill * rank;
    }

    printf("hi from rank %d\n", rank);
    fflush(stdout);
    for (m = m_start; m <= m_finish; m++) {
        u[k + 1][m] = u[k][m] + dt * (func(k * dt, m * dx) -
                                        (u[k][m] - u[k][m - 1]) / dx);
    }

}

void fill_init_conditions() {

    dx = (double) X / M;
    dt = (double) T / K;

    u = (double**) malloc(sizeof(double*) * K);
    assert(u);

    int i;
    for (i = 0; i < K; i++) {
        u[i] = (double*) malloc(sizeof(double) * M);
        assert(u[i]);
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

void dump_data() {
    FILE* data_file = fopen("parallel_data.txt", "wb");

    int k, m;
    for (k = 0; k < K; k++) {
        fprintf(data_file, "%d time_step:\t\t", k);
        for (m = 0; m < M; m++) {
            fprintf(data_file, "%.3f\t\t", u[k][m] );
        }
        fprintf(data_file, "\n");
    }

    fclose(data_file);
}

void free_memory() {
    int i;
    for (i = 0; i < K; i++) {
        free(u[i]);
    }

    free(u);
}
