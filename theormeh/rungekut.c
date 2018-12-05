#include <stdlib.h>
#include <stdio.h>

#include "rungekut.h"

enum constants
{
  num_of_it = 10,
};

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

double* rungekut(double* (*func)(double , double* , int ), int dim,
              double x_0, double* y_0, double x_1)
{
  //double k_1[dim], k_2[dim], k_3[dim], k_4[dim];
  double h = (x_1 - x_0) / num_of_it;
  int i = 0;
  double x_cur, *y_cur, *k_1, *k_2, *k_3, *k_4;

  for(i = 1; i <= num_of_it; i++)
  {
    /*
     *  k_1 = f(x_n, y_n)
     *  k_2 = f(x_n + h/2, y_n + h/2 * k_1);
     *  k_3 = f(x_n + h/2, y_n + h/2 * k_2);
     *  k_4 = f(x_n + h, y_n + h * k_3);
     */
    k_1 = func(x_cur, y_cur, dim);
    k_2 = func(x_cur + h / 2, vec_sum(y_cur, mul_vec_and_num(k_1, dim, h / 2), dim), dim);
    k_3 = func(x_cur + h / 2, vec_sum(y_cur, mul_vec_and_num(k_2, dim, h / 2), dim), dim);
    k_4 = func(x_cur + h, vec_sum(y_cur, mul_vec_and_num(k_3, dim, h), dim), dim);

    //y_{n+1} = y_n + h/6 * (k_1 + 2*k_2 + 2*k_3 + k_4);
    
    //1. h/6 * k_1 + h/3 * k_2
    double* temp_1 = vec_sum(mul_vec_and_num(k_1, dim, h/6), mul_vec_and_num(k_2, dim, h/3), dim);
    //1. h/3 * k_3 + h/6 * k_4
    double* temp_2 = vec_sum(mul_vec_and_num(k_3, dim, h/3), mul_vec_and_num(k_4, dim, h/6), dim);
    double* temp_3 = mul_vec_and_num(vec_sum(temp_1, temp_2, dim), dim, h/6);
    y_cur = vec_sum(y_cur, temp_3, dim);
  }

  return y_cur;
}
