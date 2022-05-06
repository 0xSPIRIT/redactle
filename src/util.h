#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long file_length(FILE *file);
char *readfile(char *filepath, size_t *o_length);

#endif	/* UTIL_H_ */
