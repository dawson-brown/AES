#include "file_handler.h"

FILE *file_open(char *filename){

	FILE* file = fopen(filename, "r");

	if (file != NULL){
		return file;

	} else {
		printf("Error opening file: %s. Exiting...\n", filename);
		exit(0);
	}

}

char *file_open_read(char *filename){

	FILE* file = file_open(filename);

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	rewind(file);

	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, file);
	fclose(file);

	string[fsize] = 0;

	return string;

}

char *read_file(FILE *file, int bytes){

	char *string = malloc(bytes + 1);
	fgets(string, bytes, file);
	return string;

}
