#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

long file_length(FILE *file);
char *readfile(char *filepath, size_t *o_length);
bool point_in_rect(int x, int y, SDL_Rect r);

#endif  /* UTIL_H_ */
