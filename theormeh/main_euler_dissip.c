#include <stdlib.h>
#include <stdio.h>

#include "makeSimulation.h"

int main(int argc, char* argv[])
{
  system("mkdir euler_case_dissip; mkdir euler_case_dissip/frames");
  FILE* data_t = fopen("euler_case_dissip/data_t", "w");
  FILE* data_w = fopen("euler_case_dissip/data_w", "w");
  FILE* data_a = fopen("euler_case_dissip/data_a", "w");
  FILE* data_n = fopen("euler_case_dissip/data_n", "w");

  if(!(data_t && data_w && data_a && data_n))
  {
    perror("files");
    exit(EXIT_FAILURE);
  }

  makeEulerCase(data_t, data_w, data_a, data_n);
  return 0;
}

