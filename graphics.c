#include "graphics.h"

extern byte *VGA;

void setVideoMode(byte mode)
{
    union REGS regs;
    
    regs.h.ah = 0x00;
    regs.h.al = mode;
    int86(0x10, &regs, &regs);
}

void plotPixel(int x, int y, byte colour)
{
    VGA[y*SCREEN_WIDTH+x] = colour;
}

void drawSprite(sprite_t *s)
{
    int i, j;
    byte pixel;
    for(i = 0; i < s->height; i++)
    {
        for(j = 0; j < s->width; j++)
        {
            if(pixel = s->pixels[j * s->width + i] != -1) {
                plotPixel(s->x + j, s->y + i, pixel);
            }
        }
    }
}

void fillScreen(byte colour)
{
    int x, y;
    for(y = 0; y < SCREEN_HEIGHT; y++)
    {
        for(x = 0; x < SCREEN_WIDTH; x++)
        {
            plotPixel(x, y, colour);
        }
    }
}
