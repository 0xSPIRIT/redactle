#include "input.h"

#include "globals.h"
#include "font.h"

struct Input input;

void input_type(struct Input *input, char c) {
    if (input->word.len < 64)
        input->word.str[input->word.len++] = c;
}

void input_backspace(struct Input *input) {
    if (input->word.len > 0)
        input->word.str[--input->word.len] = 0;
}

void input_draw(struct Input *input) {
    int w, h;
    font_text_size(input->font, FONT_LARGE, input->word.str, &w, &h);
    SDL_Rect r = {0, window_height-h-4, window_width, h+2};
    SDL_SetRenderDrawColor(renderer, 237,192,97,255);
    SDL_RenderDrawRect(renderer, &r);
    font_draw(input->font, input->word.str, 3, window_height-h-3, FONT_LARGE, (SDL_Color){237,192,97,255}, NULL, NULL);

    r.x = 3+w;
    r.y = window_height-h-3;
    r.w = 2;
    r.h = h;
    SDL_RenderDrawRect(renderer, &r);
}

void input_enter(struct Input *input, struct Text *text) {
    struct Line *l;
    
    for (l = text->line_start; l; l = l->next) {
        int i;
        for (i = 0; i < l->len; i++) {
            struct Word *w = &l->words[i];
            if (w->obfuscated && 0==stricmp(w->str, input->word.str)) {
                w->obfuscated = false;
            }
        }
    }

    /* Check if the title was unobfuscated. If so, then you win. */
    if (text->line_start->is_title) {
        bool is_title_unobfuscated = true;
        int i;
        for (i = 0; i < text->line_start->len; i++) {
            struct Word *w = &(text->line_start->words[i]);
            if (w->obfuscated) {
                is_title_unobfuscated = false;
            }
        }
        if (is_title_unobfuscated) {
            text_unobfuscate_all(text);
            text->won = true;
        }
    }

    memset(input->word.str, 0, 64);
    input->word.len = 0;
}
