#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int T, X, K, M;
double **u;

double  func(double t, double x);
double  psi(double t);
double  phi(double x);
void    fill_matrix();
void    dump_data();
void    free_memory();

int main(int argc, char **argv) {

    T = (argc >= 2) ? atoi( argv[1] ) : 10;
    K = (argc >= 3) ? atoi( argv[2] ) : 5;
    X = (argc >= 4) ? atoi( argv[3] ) : 10;
    M = (argc >= 5) ? atoi( argv[4] ) : 5;

    fill_matrix();
    dump_data(u, K, M);
    free_memory();
    return 0;
}

void fill_matrix() {

    double dx = (double) X / M;
    double dt = (double) T / K;

    u = (double**) malloc(sizeof(double*) * K);
    assert(u);

    int i;
    for (i = 0; i < K; i++) {
        u[i] = (double*) malloc(sizeof(double) * M);
        assert(u[i]);
    }

    int k, m;
    for (m = 0; m < M; m++) {
        u[0][m] = phi(m * dx);
    }
    for (k = 0; k < (K - 1); k++) {
        u[k + 1][0] = psi((k + 1) * dt);
        for (m = 1; m < M; m++) {
            u[k + 1][m] = u[k][m] + dt * (func(k * dt, m * dx) -
                                    (u[k][m] - u[k][m - 1]) / dx);
        }
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
    FILE* data_file = fopen("sequential_data.txt", "wb");

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
