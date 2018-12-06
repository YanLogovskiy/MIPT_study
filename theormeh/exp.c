#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>

#include "exp.h"

double* exp_(double t, double* x)
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
