#include <stdlib.h>
#include <stdio.h>

#include "rungekut.h"
#include "exp.h"

int main(int argc, char* argv[])
{
  double x_0 = 1;
  double x_1 = 2;
  int dimension = 2;
  double y_0[2];
  y_0[0] = 1;
  y_0[1] = 1;

  double* y_1 = rungekut(&exp_, dimension, x_0, y_0, x_1);

  printf("\n\tx_0 = %f\t, y_0 = (%f\t, %f)\n"
         "\tx_1 = %f\t, y_1 = (%f\t, %f)\n"
          , x_0, y_0[0], y_0[1], x_1, y_1[0], y_1[1]);

  return 0;
}

