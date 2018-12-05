#ifndef RUNGE
#define RUNGE


double* vector_sum(double* a, double* b, int dimension);


double* rungekut((double*) func, int dimension, 
              double x_0, double y_0, double x_1);



#endif //RUNGE
