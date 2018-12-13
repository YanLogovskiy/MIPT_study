#ifndef ANIM
#define ANIM
#include <stdio.h>

struct Vector
{
  double x;
  double y;
  double z;
  double t;
};

int makeOscillation(FILE* data_t, FILE* data_x);

int makeEulerCase(FILE* data_t, FILE* data_a, FILE* data_b, FILE* data_c);

struct Vector* rotateVector(double tetta, double phi, double ksi,
    struct Vector vec);

#endif //ANIM
