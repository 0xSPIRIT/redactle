#include "util.h"
#include "ctype.h"

long file_length(FILE *file) {
    long length;
    
    long pos = ftell(file);
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, pos, SEEK_SET);

    return length;
}

char *readfile(char *filepath, size_t *o_length) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
	fprintf(stderr, "Error opening %s.\n", filepath);
	exit(1);
    }

    size_t length = file_length(file)+1;
    char *buffer = malloc(length);
    length = fread(buffer, 1, length, file);
    if (o_length != NULL) {
        *o_length = length;
    }
    buffer[length] = 0;

    fclose(file);
    
    return buffer;
}
