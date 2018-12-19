#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "makeSimulation.h"
#include "diff_eq_models.h"
#include "math_func.h"

void makeOscillation(FILE* data_t, FILE* data_x)
{
  double t_0, t_1;
  t_0 = 0; t_1 = 62.8;
  int i, num_of_cadres, dim;  //because we make video with 25 frames per second
  i = 0; num_of_cadres = t_1 * 25; dim = 2;

  double x_0[dim];
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
    x_cur = rungekut(&oscillator, dim, t_cur, x_cur, t_cur + t_step);
    t_cur += t_step;
    t[i] = t_cur;
    x[i] = x_cur[0];
  }

  fwrite(t, sizeof(double), num_of_cadres, data_t);
  fwrite(x, sizeof(double), num_of_cadres, data_x);
}


void makeEulerCase(FILE* data_t, FILE* data_w, FILE* data_a, FILE* data_n)
{
  double t_0, t_1;
  t_0 = 0; t_1 = 0.5;
  int i, num_of_cadres, dim;   
  i = 0; num_of_cadres = t_1 * 500; dim = 3;
  double t_step = (t_1 - t_0) / (num_of_cadres - 1); //one for init condition

  double t[num_of_cadres], w[num_of_cadres][dim], p, q, r;
  t[0] = t_0; p = w[0][0] = 0; q = w[0][1] = 1; r = w[0][2] = 80;

  double A, B, C, K, tetta, phi, ksi,  ksi_d;
  A = 80; B = 80; C = 1; ksi = 0;
  K = sqrt(pow(A*p, 2) + pow(B*q, 2) + pow(C*r, 2));
  tetta = acos(C*r/K);
  if(tetta == 0)
    phi = ksi_d = 0;
  else
  {
    phi   = acos(B*q/(K*sin(tetta)));
    ksi_d = (p * sin(phi) + q * cos(phi)) / sin(tetta);
  }
  ksi   = ksi + ksi_d * t_step;  
  
  struct Vector a_array[num_of_cadres], n_array[num_of_cadres];
  a_array[0].x = 0; a_array[0].y = 1; a_array[0].z = 4;
  n_array[0].x = 0; n_array[0].y = -1; n_array[0].z = 0;

  printf("\t x = %f\t y = %f\t z = %f\n", a_array[i].x, a_array[i].y, a_array[i].z);
  //printf("\tp %f\t q %f\t r %f\n", p, q, r);
  //printf("\ttetta %f\t phi %f\t ksi %f\n", tetta, phi, ksi);

  for(i = 1; i < num_of_cadres; i++)
  {
    t[i] = t[i-1] + t_step;

    p = w[i][0] = (rungekut(&EulerCase, dim, t[i-1], w[i-1], t[i]))[0];
    q = w[i][1] = (rungekut(&EulerCase, dim, t[i-1], w[i-1], t[i]))[1];
    r = w[i][2] = (rungekut(&EulerCase, dim, t[i-1], w[i-1], t[i]))[2];

    K = sqrt(pow(A*p, 2) + pow(B*q, 2) + pow(C*r, 2));
    tetta = acos(C*r/K);
    if(tetta == 0)
    phi = ksi_d = 0;
    else
    {
      phi   = acos(B*q/(K*sin(tetta)));
      ksi_d = (p * sin(phi) + q * cos(phi)) / sin(tetta);
    }
    ksi   = ksi + ksi_d * t_step;
    
    a_array[i] = *rotateVector(tetta, phi, ksi, a_array[0]);
    n_array[i] = *rotateVector(tetta, phi, ksi, n_array[0]);

    printf("\t x = %f\t y = %f\t z = %f\n", a_array[i].x, a_array[i].y, a_array[i].z);
    //printf("\tp %f\t q %f\t r %f\n", p, q, r);
    //printf("\ttetta %f\t phi %f\t ksi %f\n", tetta, phi, ksi);
  }
  fwrite(t, sizeof(double), num_of_cadres, data_t);
  fwrite(w, sizeof(double) * dim, num_of_cadres, data_w);
  fwrite(a_array, sizeof(struct Vector), num_of_cadres, data_a);
  fwrite(n_array, sizeof(struct Vector), num_of_cadres, data_n);
}

struct Vector* rotateVector(double tetta, double phi, double ksi,
    const struct Vector vec)
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
  res_vec = mul_matrix_and_vec(res_vec, 3, rotation_2);

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
