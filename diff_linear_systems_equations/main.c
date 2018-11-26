#include <stdlib.h>
#include <stdio.h>


#include "generateSolutionFile.h"

#define CHECK_COM_LINE_ARG(argc)                                  \
if(argc != 2)                                                      \
    {                                                             \
        printf("\n\tYou have to enter name of the programm"       \
                        "and name of file with data\n");\
        exit(EXIT_FAILURE);                                       \
    }

#define ERROR_OPENING(file_name)                                \
{                                                           \
  perror(#file_name);                                     \
  exit(EXIT_FAILURE);                                     \
}

int main(int argc, char* argv[])
{
  CHECK_COM_LINE_ARG(argc)
  
  FILE* input_matrix_file = fopen(argv[1], "r");
  if(!input_matrix_file)
    ERROR_OPENING(argv[1]);

  generateSolutionFile(input_matrix_file);
  return 0;
}
