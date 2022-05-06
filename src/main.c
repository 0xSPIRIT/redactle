#include <stdio.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "globals.h"
#include "text.h"
#include "util.h"

int main(void) {
    bool running = true;
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("redactle",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              window_width,
                              window_height,
                              0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    
    struct Font *font;
    font = font_allocate("../bin/consola.ttf");

    struct Text *text;
    char *str = readfile("../bin/text.txt", NULL);
    
    text = text_allocate(font, str);
    
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;

	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	    SDL_RenderClear(renderer);

	    text_draw(text);
	    
	    SDL_RenderPresent(renderer);
        }
    }

    free(str);
    
    text_deallocate(text);
    font_deallocate(font);
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
    TTF_Quit();
    
    return 0;
}
