#ifndef GRAPHICS_H
#define GRAPHICS_H

//#include <dos.h>
#include <stdlib.h>

#define VIDEO_INT 0x10
#define WRITE_DOT 0x0C
#define SET_MODE 0x00
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define NUM_COLORS 256

#define SPRITE_DIM 20
#define SPRITE_SIZE 400

#define MAX_SPRITES_X SCREEN_WIDTH/SPRITE_DIM
#define MAX_SPRITES_Y SCREEN_HEIGHT/SPRITE_DIM

//#define plotPixel(x, y, colour) VGA[(y)*SCREEN_WIDTH+(x)] = (colour)
#define plotPixel(x, y, colour) VGA[((y) << 8) + ((y) << 6) + x] = colour

typedef unsigned char byte;
typedef unsigned short word;

typedef enum Colour {
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LtGrey,
    DkGrey,
    LtBlue,
    LtGreen,
    LtCyan,
    LtRed,
    LtMagenta,
    Yellow,
    White
} colour_t;

typedef struct Pixel {
    int x;
    int y;
    byte c;
} pixel_t;

typedef struct Sprite {
    int x;
    int y;
    pixel_t *pixels;
} sprite_t;

extern void set_video_mode(byte mode);

sprite_t load_sprite(char *fname);
void draw_sprite(sprite_t *s);
void free_sprite(sprite_t *s);

void fill_screen(byte colour);
void colour_test_16();

#endif
