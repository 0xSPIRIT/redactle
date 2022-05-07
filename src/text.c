#include "text.h"

#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "util.h"

bool is_word_obfuscated(char *str) {
    char *comps[] =
        {
            "the",
            "be",
            "of",
            "and",
            "a",
            "in",
            "to",
            "is",
            "have",
            "it",
            "for",
            "i",
            "that",
            "you",
            "he", "she",
            "on",
            "with",
            "do",
            "at",
            "by",
            "not",
            "this",
            "but",
            "from",
            "they", "their",
        };
    int i;
    int len = sizeof(comps)/sizeof(*comps);
    for (i = 0; i < len; i++) {
        if (0==stricmp(str, comps[i])) {
            return false;
        }
    }
    return true;
}

void text_unobfuscate_all(struct Text *text) {
    struct Line *l;
    
    printf("start\n");fflush(stdout);
    for (l = text->line_start; l; l = l->next) {
        int i;
        for (i = 0; i < l->len; i++) {
            l->words[i].obfuscated = false;
        }
    }
    printf("Stopped\n");fflush(stdout);
}

struct Text *text_allocate(struct Font *font, char *str) {
    struct Text *text = calloc(1, sizeof(struct Text));
    struct Line *line;

    text->font = font;

    line = line_allocate(text);
    line->y = 0;
    text->line_start = line;
    text->line_start->is_title = true;
    
    if (*str == '>' && *(str+1) == ' ') {
        str += 2;
        line->size = FONT_LARGE;
    }
    
    while (*str) {
        if (*str == '\n' || *str == '\r') {
            if (*str == '\r' && *(str+1) == '\n') {
                str += 2;
            } else {
                ++str;
            }
            line->words[line->len-1].obfuscated = is_word_obfuscated(line->words[line->len-1].str);
            line->next = line_allocate(text);
            line->next->y = line->y+1;
            line->next->prev = line;
            line = line->next;

            /* Checking for header flag. */
            if (*str == '>' && *(str+1) == ' ') {
                str += 2;
                line->size = FONT_LARGE;
            }
            continue;
        } else if (*str == ' ' || *str == ',') {
            line->words[line->len-1].obfuscated = is_word_obfuscated(line->words[line->len-1].str);
            line->len++;
            str++;
            continue;
        }
        line->words[line->len-1].str[line->words[line->len-1].len++] = *str;
        ++str;
    }
    return text;
}

void text_deallocate(struct Text *text) {
    /* TODO: Free lines. */
    free(text);
}

void text_draw(struct Text *text) {
    struct Line *line;
    int acc = 0;
    
    for (line = text->line_start; line; line = line->next) {
        acc += line_draw(line, acc) + 3;
    }
}


struct Line *line_allocate(struct Text *text) {
    struct Line *line = calloc(1, sizeof(struct Line));
    line->text = text;
    line->len = 1;
    line->size = FONT_MEDIUM;
    memset(line->words, 0, 64 * sizeof(struct Word));
    return line;
}

void line_deallocate(struct Line *line) {
    free(line);
}

/* Draws line and returns the height. */
int line_draw(struct Line *line, int yoff) {
    struct Font *font = line->text->font;
    int i;
    int h;
    int acc = 0;
    for (i = 0; i < line->len; i++) {
        int w;
        SDL_Rect r;
        font_text_size(font, line->size, line->words[i].str, &w, &h);
        r.x = 8+acc;
        r.y = 8+yoff;
        r.w = w;
        r.h = h;
        line->words[i].rect = r;
        if (line->words[i].obfuscated) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &r);
        } else {
            font_draw(font, line->words[i].str, 8+acc, 8+yoff, line->size, WHITE, &w, &h);
        }
        acc += w + font->char_w[line->size];
    }
    return h;
}
