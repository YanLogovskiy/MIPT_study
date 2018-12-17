#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>

#include "diff_eq_models.h"

double* oscillator(double t, double* x)
{
  double l_0 = 1;
  double omega = 0.1;

  double* x_diff = (double*) calloc(2, sizeof(double));
  /* x_vector = (x, v)
   * x'  = v
   * x'' = -w^2 (x - l_0) */
  x_diff[0] = x[1]; 
  x_diff[1] = - omega * omega * (x[0] - l_0); 
  //l_0 - lenght of a spring in unstreched condition

  return x_diff;
}

double* EulerCase(double t, double* w)
{
  //main moments of inertia
  double A, B, C;
  A = 81; B = 80; C = 1;

  double* w_diff = (double*) calloc(3, sizeof(double));
  /* w_vector = (p, q, r)
   * p' = (B - C)qr/A
   * q' = (C - A)pr/B
   * r' = (A - B)pq/C */
  w_diff[0] = (B - C) * w[1] * w[2] / A;
  w_diff[1] = (C - A) * w[0] * w[2] / B;
  w_diff[2] = (A - B) * w[0] * w[1] / C;

  return w_diff;
}
