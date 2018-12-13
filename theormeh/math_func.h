#ifndef RUNGE
#define RUNGE

double* vec_sum(double* a, double* b, int dim);
double* mul_vec_and_num(double* a, int dim, double num);
double* rungekut(double* (*func)(double , double* ), int dim,
              double x_0, double* y_0, double x_1);

double* mul_matrix_and_vec(double* vec, int dim, double matrix[dim][dim]);





#endif //RUNGE
