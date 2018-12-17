#include <stdlib.h>
#include <stdio.h>

#include "makeSimulation.h"

int main(int argc, char* argv[])
{
  system("mkdir euler_case; mkdir euler_case/frames");
  FILE* data_t = fopen("euler_case/data_t", "w");
  FILE* data_w = fopen("euler_case/data_w", "w");
  FILE* data_a = fopen("euler_case/data_a", "w");
  FILE* data_n = fopen("euler_case/data_n", "w");

  if(!(data_t && data_w && data_a && data_n))
  {
    perror("files");
    exit(EXIT_FAILURE);
  }

  makeEulerCase(data_t, data_w, data_a, data_n);
  return 0;
}

