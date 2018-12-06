#include <stdlib.h>
#include <stdio.h>

#include "rungekut.h"
#include "makeAnimation.h"

int main(int argc, char* argv[])
{
  FILE* data_file_t = fopen("data_t", "w");
  FILE* data_file_x = fopen("data_x", "w");
  if(!data_file_t || !data_file_x)
  {
    perror("data_files");
    exit(EXIT_FAILURE);
  }

  makeAnimation(data_file_t, data_file_x);
  return 0;
}

