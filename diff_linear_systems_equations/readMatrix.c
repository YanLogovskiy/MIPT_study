#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "readMatrix.h"

double* readMatrix(char* buf)
{
  assert(buf);
  size_t slider = 0;
  int num_of_lines, num_of_columns;
  num_of_lines = num_of_columns = 0;
  //there we assume that our matrix is square
  //in another case there is no sence...
  while(buf[slider] != '\0')
    if(buf[slider++] == '\n')
      num_of_lines++;

  num_of_columns = num_of_lines;
  printf("lines = %d\n", num_of_lines);

  
}
