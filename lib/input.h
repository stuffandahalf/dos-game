#ifndef INPUT_H
#define INPUT_H

#include "types.h"

#define ESCAPE 0x1B
#define ARROW_UP 0x48
#define ARROW_LEFT 0x4B
#define ARROW_RIGHT 0x4D
#define ARROW_DOWN 0x50

typedef struct Mouse {
    word available;
    word num_buttons;
    word x;
    word y;
    byte active;
} mouse_t;

/* getKey returns a word with the scancode in the upper 8 bits and the ascii value in the lower 8 */
word get_key_bios();
byte get_key_dos();
void mouse_init(mouse_t *m);
void mouse_update(mouse_t *m);

#endif
