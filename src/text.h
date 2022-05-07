#ifndef TEXT_H_
#define TEXT_H_

#include <stdbool.h>

#include "font.h"

struct Text {
    struct Font *font;
    struct Line *line_start;    /* Doubly linked list of lines. */
    bool won;                   /* Is the game won? */
};

struct Text *text_allocate(struct Font *font, char *str);
void text_deallocate(struct Text *text);
void text_draw(struct Text *text);
void text_unobfuscate_all(struct Text *text);

struct Word {
    char str[64];
    int len;                    /* Length of string. */
    bool obfuscated;
    SDL_Rect rect;              /* Position of the text. Used for mouse interactions.
                                   This gets set when drawn. */
};

struct Line {
    struct Line *prev, *next;
    struct Text *text;          /* Text the font belongs to. */
    struct Word words[64];
    int len;                    /* Amount of words. */
    int size;                   /* FONT_SMALL/MEDIUM/LARGE */
    int y;                      /* Line number. */
    bool is_title;              /* Is this the title of the text? */
};

struct Line *line_allocate(struct Text *text);
void line_deallocate(struct Line *line);
int line_draw(struct Line *line, int yoff);

bool is_word_obfuscated(char *str);

#endif  /* TEXT_H_ */
