#include <stdlib.h>
#include <stdio.h>

#include "makeSimulation.h"

int main(int argc, char* argv[])
{
  system("mkdir euler_case; mkdir euler_case/frames");
  FILE* data_t = fopen("euler_case/data_t", "w");
  FILE* data_w = fopen("euler_case/data_w", "w");
  FILE* data_a = fopen("euler_case/data_a", "w");
  FILE* data_b = fopen("euler_case/data_b", "w");
  FILE* data_c = fopen("euler_case/data_c", "w");

  if(!(data_t && data_w && data_a && data_b && data_c))
  {
    perror("files");
    exit(EXIT_FAILURE);
  }

  makeEulerCase(data_t, data_w, data_a, data_b, data_c);
  return 0;
}

