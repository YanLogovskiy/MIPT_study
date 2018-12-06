#include <stdlib.h>
#include <stdio.h>

#include "rungekut.h"
#include "exp.h"

int main(int argc, char* argv[])
{
  double t_0 = 0;
  double t_1 = 10;
  int i, num_of_cadres = 10;
  int dimension = 2;
  double x_0[2];
  x_0[0] = 2; //x_0 = 2
  x_0[1] = 0; //v_0 = 0

  double t_step = (t_1 - t_0) / num_of_cadres;
  double t_cur = t_0;
  double *x_cur = x_0;
  printf("\n\tt_cur = %f\t, x_cur = (%f\t, %f)\n", t_cur, x_cur[0], x_cur[1]);
  for(i = 0; i < num_of_cadres; i++)
  {
    x_cur = rungekut(&exp_, dimension, t_cur, x_cur, t_cur + t_step);
    printf("\n\tt_cur = %f\t, x_cur = (%f\t, %f)\n", t_cur, x_cur[0], x_cur[1]);
    t_cur += t_step;
  }
  return 0;
}

