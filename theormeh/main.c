#include <stdlib.h>
#include <stdio.h>

#include "rungekut.h"
#include "makeSimulation.h"

int main(int argc, char* argv[])
{
  FILE* data_file_t = fopen("oscillation/data_t", "w");
  FILE* data_file_x = fopen("oscillation/data_x", "w");
  if(!data_file_t || !data_file_x)
  {
    perror("data_files");
    exit(EXIT_FAILURE);
  }

  makeOscillation(data_file_t, data_file_x);
  return 0;
}

