#include <stdio.h>
#include <stdlib.h>

#include "makeSimulation.h"
#include "diff_eq_models.h"
#include "rungekut.h"

int makeOscillation(FILE* data_t, FILE* data_x)
{
  double t_0, t_1;
  t_0 = 0; t_1 = 62.8;
  int i, num_of_cadres, dimension;  //because we make video with 25 frames per second
  i = 0; num_of_cadres = t_1 * 25; dimension = 2;

  double x_0[dimension];
  x_0[0] = 2; x_0[1] = 0; //x_0 = 2 v_0 = 0

  double t_step, t_cur, *x_cur;
  t_step = (t_1 - t_0) / (num_of_cadres - 1); //one for init condition
  t_cur = t_0; x_cur = x_0;

  //these arrays are for dumping in file python will work with
  double t[num_of_cadres], x[num_of_cadres];
  t[0] = t_0;
  //there we don't need velocity, so x is a scalar array
  x[0] = x_0[0];

  for(i = 1; i < num_of_cadres; i++)
  {
    x_cur = rungekut(&oscillator, dimension, t_cur, x_cur, t_cur + t_step);
    t_cur += t_step;
    t[i] = t_cur;
    x[i] = x_cur[0];
  }

  fwrite(t, sizeof(double), num_of_cadres, data_t);
  fwrite(x, sizeof(double), num_of_cadres, data_x);
  return 0;
}

struct Point
{
  double x;
  double y;
  double z;
  double t;
};

int makeEulerCase(FILE* data_a, FILE* data_b, FILE* data_c)
{
  double t_0, t_1;
  t_0 = 0; t_1 = 10;
  int i, num_of_cadres, dimension;  //because we make video with 25 frames per second
  i = 0; num_of_cadres = t_1 * 25; dimension = 3;
  double w_0[dimension];
  w_0[0] = 1; w_0[1] = 1; w_0[2] = 1; //p=1, q=1, r=1

  double t_step, t_cur, *w_cur;
  t_step = (t_1 - t_0) / (num_of_cadres - 1); //one for init condition
  t_cur = t_0; w_cur = w_0;

  //these arrays are for dumping in file python will work with
  double t[num_of_cadres], *w_array[num_of_cadres];
  t[0] = t_0; w_array[0] = w_0;

  for(i = 1; i < num_of_cadres; i++)
  {
    w_cur = rungekut(&EulerCase, dimension, t_cur, w_cur, t_cur + t_step);
    t_cur += t_step;
    t[i] = t_cur;
    w_array[i] = w_cur;
  }
 
  //fwrite(t, sizeof(double), num_of_cadres, data_t);
  return 0;
}

