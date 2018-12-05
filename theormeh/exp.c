#include <stdlib.h>
#include <stdio.h>

#include "exp.h"

double* exp_(double x, double* y)
{
  double* y_diff = (double*) calloc(2, sizeof(double));
  y_diff[0] = y[0];
  y_diff[1] = y[1];

  return y_diff;
}
