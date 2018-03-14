#ifndef GRAPHICS_H
#define GRAPHICS_H

//#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define VIDEO_INT 0x10
#define WRITE_DOT 0x0C
#define SET_MODE 0x00
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define NUM_COLORS 256

#define SPRITE_DIM 20
#define MAX_SPRITES_X SCREEN_WIDTH/SPRITE_DIM
#define MAX_SPRITES_Y SCREEN_HEIGHT/SPRITE_DIM

//#define plotPixel(x, y, colour) VGA[(y)*SCREEN_WIDTH+(x)] = (colour)
#define plot_pixel(x, y, colour) VGA[((y) << 8) + ((y) << 6) + x] = (colour)


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

typedef struct Sprite {
    word x;
    word y;
    word width;
    word height;
    byte *data;
} sprite_t;

extern void set_video_mode(byte mode);

void fskip(FILE *fp, int num_bytes);
void load_bmp(char *file, sprite_t *s);

void draw_sprite(sprite_t *s);
void clear_sprite(sprite_t *s);
void free_sprite(sprite_t *s);

void move_sprite_right(sprite_t *s);

void fill_screen(byte colour);
void colour_test_16();

#endif
