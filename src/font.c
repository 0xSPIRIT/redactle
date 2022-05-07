#include "font.h"

#include <stdlib.h>

#include "globals.h"

struct Font *font_allocate(const char *fp) {
    struct Font *font = calloc(1, sizeof(struct Font));
    font->small = TTF_OpenFont(fp, 14);
    font->medium = TTF_OpenFont(fp, 24);
    font->large = TTF_OpenFont(fp, 50);
    TTF_SizeText(font->small, " ", &font->char_w[FONT_SMALL], &font->char_h[FONT_SMALL]);
    TTF_SizeText(font->medium, " ", &font->char_w[FONT_MEDIUM], &font->char_h[FONT_MEDIUM]);
    TTF_SizeText(font->large, " ", &font->char_w[FONT_LARGE], &font->char_h[FONT_LARGE]);
    return font;
}

void font_deallocate(struct Font *font) {
    TTF_CloseFont(font->small);
    TTF_CloseFont(font->medium);
    TTF_CloseFont(font->large);
    free(font);
}

void font_draw(struct Font *font, const char *text, int x, int y, int size, SDL_Color col, int *width, int *height) {
    TTF_Font *f;

    if (*text == 0) return;
    
    switch (size) {
    case FONT_SMALL:
        f = font->small;
        break;
    case FONT_MEDIUM:
        f = font->medium;
        break;
    case FONT_LARGE:
        f = font->large;
        break;
    }
    
    SDL_Surface *surf = TTF_RenderText_Blended(f, text, col);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

    if (width)
        *width = surf->w;
    if (height)
        *height = surf->h;

    SDL_Rect dst = {x, y, surf->w, surf->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}

void font_text_size(struct Font *font, int size, const char *text, int *w, int *h) {
    TTF_Font *f;
    
    switch (size) {
    case FONT_SMALL:
        f = font->small;
        break;
    case FONT_MEDIUM:
        f = font->medium;
        break;
    case FONT_LARGE:
        f = font->large;
        break;
    }

    TTF_SizeText(f, text, w, h);
}
