#ifndef FONT_H_
#define FONT_H_

#include <SDL2/SDL_ttf.h>

enum FontSize {
    FONT_SMALL,
    FONT_MEDIUM,
    FONT_LARGE,
    FONTSIZE_COUNT
};

struct Font {
    TTF_Font *small, *medium, *large;
    int char_w[FONTSIZE_COUNT],
        char_h[FONTSIZE_COUNT];
};

struct Font *font_allocate(const char *fp);
void font_deallocate(struct Font *font);
void font_draw(struct Font *font, const char *text, int x, int y, int size, SDL_Color col, int *width, int *height);
void font_text_size(struct Font *font, int size, const char *text, int *w, int *h);

#endif /* FONT_H_ */
