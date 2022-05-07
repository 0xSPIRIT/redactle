#ifndef INPUT_H_
#define INPUT_H_

#include "text.h"

struct Input {
    struct Font *font;
    struct Word word;
};

extern struct Input input;

void input_type(struct Input *input, char c);
void input_backspace(struct Input *input);
void input_draw(struct Input *input);
void input_enter(struct Input *input, struct Text *text);

#endif  /* INPUT_H_ */
