#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <SDL2/SDL.h>

#define WHITE (SDL_Color){255,255,255,255}
#define BLACK (SDL_Color){0,0,0,255}
#define RED (SDL_Color){255,0,0,255}

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern const int window_width;
extern const int window_height;

#endif	/* GLOBALS_H_ */
