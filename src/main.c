#include <stdio.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "globals.h"
#include "text.h"
#include "util.h"
#include "input.h"

int main(void) {
    bool running = true;
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Redactle",
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
    
    input.font = font;
    input.word = (struct Word){0};

    text = text_allocate(font, str);
    
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            SDL_Rect character_popup;
            int character_popup_amt = 0;
            
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_TEXTINPUT) {
                input_type(&input, *event.text.text);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if (SDL_GetModState() == KMOD_LCTRL) {
                        memset(input.word.str, 0, 64);
                        input.word.len = 0;
                    }
                    input_backspace(&input);
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    input_enter(&input, text);
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                struct Line *l;
                for (l = text->line_start; l; l = l->next) {
                    int i;
                    for (i = 0; i < l->len; i++) {
                        struct Word *w = &l->words[i];
                        if (w->obfuscated && point_in_rect(event.motion.x, event.motion.y, w->rect)) {
                            character_popup.x = event.motion.x;
                            character_popup.y = event.motion.y;
                            character_popup_amt = strlen(w->str);
                        }
                    }
                }
            }

            if (text->won)
                SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            text_draw(text);
            input_draw(&input);
            
            if (character_popup_amt) {
                char ch[24];
                sprintf(ch, "Characters: %d", character_popup_amt);
                font_text_size(font, FONT_MEDIUM, ch, &character_popup.w, &character_popup.h);
                character_popup.w += 26;
                character_popup.h += 1;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &character_popup);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &character_popup);
                font_draw(font, ch, character_popup.x+20, character_popup.y+1, FONT_MEDIUM, WHITE, NULL, NULL);
            }
            
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
