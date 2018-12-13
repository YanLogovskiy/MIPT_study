#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "makeSimulation.h"
#include "diff_eq_models.h"
#include "math_func.h"

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


int makeEulerCase(FILE* data_t, FILE* data_a, FILE* data_b, FILE* data_c)
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

  double A, B, C, K, tetta, phi, ksi,  ksi_d;
  A = B = 3; C = 1; ksi = 0; //ksi_0 = 0
  K = sqrt(pow(A*w_cur[0], 2) + pow(B*w_cur[1], 2) + pow(C*w_cur[2], 2));
  tetta = acos(C*w_cur[2]/K);
  phi   = acos(B*w_cur[1]/(K*sin(tetta)));
  ksi_d = (w_cur[0] * sin(phi) + w_cur[1] * cos(phi)) / sin(tetta);
  ksi   = ksi + ksi_d * t_step;

  //these arrays are for dumping in file python will work with
  double t[num_of_cadres], *w_array[num_of_cadres];
  t[0] = t_0; w_array[0] = w_0;
  struct Vector a_array[num_of_cadres], b_array[num_of_cadres], c_array[num_of_cadres];
  for(i = 1; i < num_of_cadres; i++)
  {
    w_cur = rungekut(&EulerCase, dimension, t_cur, w_cur, t_cur + t_step);
    t_cur += t_step;
    t[i] = t_cur;
    w_array[i] = w_cur;

    tetta = acos(C*w_cur[2]/K);
    phi   = acos(B*w_cur[1]/(K*sin(tetta)));
    ksi_d = (w_cur[0] * sin(phi) + w_cur[1] * cos(phi)) / sin(tetta);
    ksi   = ksi + ksi_d * t_step;

  }


 
  //fwrite(t, sizeof(double), num_of_cadres, data_t);
  return 0;
}

struct Vector* rotateVector(double tetta, double phi, double ksi,
    struct Vector vec)
{
  double vec_[3];
  vec_[0] = vec.x; vec_[1] = vec.y; vec_[2] = vec.z;
  double rotation_1[3][3] = {};
  rotation_1[0][0] = cos(ksi);
  rotation_1[0][1] = -sin(ksi);
  rotation_1[1][0] = sin(ksi);
  rotation_1[1][1] = cos(ksi);
  rotation_1[2][2] = 1;
  double* res_vec = mul_matrix_and_vec(vec_, 3, rotation_1);
  
  double rotation_2[3][3] = {};
  rotation_2[0][0] = 1;
  rotation_2[1][1] = cos(tetta);
  rotation_2[1][2] = -sin(tetta);
  rotation_2[2][1] = sin(tetta);
  rotation_2[2][2] = cos(tetta);
  res_vec = mul_matrix_and_vec(vec_, 3, rotation_2);

  double rotation_3[3][3] = {};
  rotation_3[0][0] = cos(phi);
  rotation_3[0][1] = -sin(phi);
  rotation_3[1][0] = sin(phi);
  rotation_3[1][1] = cos(phi);
  rotation_3[2][2] = 1;
  res_vec = mul_matrix_and_vec(res_vec, 3, rotation_3);

  struct Vector* vec_p = (struct Vector*) calloc(1, sizeof(struct Vector));
  vec_p->x = res_vec[0]; vec_p->y = res_vec[1]; vec_p->z = res_vec[2];

  return vec_p;
}
