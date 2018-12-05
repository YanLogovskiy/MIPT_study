#include <stdlib.h>
#include <stdio.h>

#include "rungekut.h"

enum constants
{
  number_of_iterations = 10,
}

double* vec_sum(double* a, double* b, int dim)
{
  double* res_vec = (double*) calloc(dim, sizeof(double));
  for(int i = 0; i < dim; i++)
    res_vec[i] = a[i] + b[i];

  return res_vec;
}

double* mul_vec_and_num(double* a, int dim, double num)
{
  double* res_vec = (double*) calloc(dim, sizeof(double));
  for(int i = 0; i < dim; i++)
    res_vec[i] = num * a[i];

  return res_vec;

}

double* rungekut((double*) func(double x, double* y), int dim, 
              double x_0, double* y_0, double x_1)
{
  double k_1[dim], k_2[dim], k_3[dim], k_4[dim];
  double h = (x_1 - x_0) / number_of_iterations;
  int i = 0;
  double x_cur, *y_cur;

  for(i = 1; i <= number_of_iterations; i++)
  {
    /*
     *  k_1 = f(x_n, y_n)
     *  k_2 = f(x_n + h/2, y_n + h/2 * k_1);
     *  k_3 = f(x_n + h/2, y_n + h/2 * k_2);
     *  k_4 = f(x_n + h, y_n + h * k_3);
     */
    k_1 = func(x_cur, y_cur);
    k_2 = func(x_cur + h / 2, vec_sum(y_cur, mul_vec_and_num(k_1, dim, h / 2), dim);
    k_3 = func(x_cur + h / 2, vec_sum(y_cur, mul_vec_and_num(k_2, dim, h / 2), dim);
    k_4 = func(x_cur + h, vec_sum(y_cur, mul_vec_and_num(k_3, dim, h), dim);

    //y_{n+1} = y_n + h/6 * (k_1 + 2*k_2 + 2*k_3 + k_4);
    
    //1. h/6 * k_1 + h/3 * k_2
    double temp_1 = vec_sum(mul_vec_and_num(k_1, dim, h/6), mul_vec_and_num(k_2, dim, h/3), dim);



  }
}
