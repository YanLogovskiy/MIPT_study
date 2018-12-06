#include <stdio.h>
#include <stdlib.h>

#include "makeAnimation.h"
#include "exp.h"
#include "rungekut.h"

int makeAnimation(FILE* data_t, FILE* data_x)
{
  double t_0 = 0;
  double t_1 = 62.8;
  int i, num_of_cadres = 100;
  int dimension = 2;
  double x_0[2];
  x_0[0] = 2; //x_0 = 2
  x_0[1] = 0; //v_0 = 0

  double t_step = (t_1 - t_0) / (num_of_cadres - 1); //one for init condition
  double t_cur = t_0;
  double *x_cur = x_0;

  //these arrays are for dumping in file python will work with
  double t[num_of_cadres], x[num_of_cadres];
  t[0] = t_0;
  //there we don't need velocity, so x is a scalar array
  x[0] = x_0[0];

  for(i = 1; i < num_of_cadres; i++)
  {
    x_cur = rungekut(&exp_, dimension, t_cur, x_cur, t_cur + t_step);
    t_cur += t_step;
    t[i] = t_cur;
    x[i] = x_cur[0];
  }

  fwrite(t, sizeof(double), num_of_cadres, data_t);
  fwrite(x, sizeof(double), num_of_cadres, data_x);
  return 0;

}
