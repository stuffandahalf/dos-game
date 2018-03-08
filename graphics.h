#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <dos.h>

#define VIDEO_INT 0x10
#define WRITE_DOT 0x0C
#define SET_MODE 0x00
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define NUM_COLORS 256

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

typedef struct Sprite {
    int x;
    int y;
    int width;
    int height;
    byte *pixels;
} sprite_t;

void setVideoMode(byte mode);
void plotPixel(int x, int y, byte colour);
void drawSprite(sprite_t *s);
void fillScreen(byte colour);

#endif
