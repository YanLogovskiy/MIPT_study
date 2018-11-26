#include "readInBufFromFile.h"
#include <assert.h>
#include <stdlib.h>

char* readInBufFromFile(FILE* stream)
{
	assert(stream);
	fseek(stream, 0, SEEK_END);
	size_t filesize = ftell(stream);
	rewind(stream);

	char* buf = (char*) calloc(filesize + 1, sizeof(char));
	if(fread(buf, sizeof(char), filesize, stream) 
			!= filesize)
	{
		printf("\n\tCan't read from file\n");
		exit(1);
	}

	buf[filesize - 1] = '\0'; //especially for building tree
	return buf;
}
