#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "generateSolutionFile.h"

#include "readInBufFromFile.h"
#include "readMatrix.h"
#include "executeStepGauss.h"

void generateSolutionFile(FILE* input_matrix_file)
{
  assert(input_matrix_file);
  char* buf = readInBufFromFile(input_matrix_file);

  printf("%s\n", buf);
  int slider, m_size, i, j, num_len, num_read_symb;
  slider = m_size = i = j = num_len = num_read_symb = 0;
  while(buf[slider] != '\0')
    if(buf[slider++] == '\n')
      m_size++;
  int matrix[m_size][m_size];
  for(i = 0; i < m_size; i++)
    for(j = 0; j < m_size; j++)
    {
      sscanf(&(buf[num_read_symb]), "%d%n", &(matrix[i][j]), &num_len);
      num_read_symb += num_len;
    }

}

