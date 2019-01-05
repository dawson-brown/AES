#ifndef NUMBER_HANDLER
	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#define NUMBER_HANDLER
#endif

FILE *file_open(char *filename);

char *file_open_read(char *filename);

char *read_file(FILE *file, int bytes);
