#include "lib/graphics.h"
#include <stdlib.h>

extern byte *VGA;

void draw_sprite(sprite_t *s)
{
    int i, x, y;
    for(i = 0; i < SPRITE_SIZE; i++)
    {
        x = s->x + s->pixels[i].x;
        y = s->y + s->pixels[i].y;
        plotPixel(x, y, s->pixels[i].c);
    }
}

void fill_screen(byte colour)
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

void free_sprite(sprite_t *s)
{
    free(s->pixels);
    free(s);
}

void colour_test_16()
{
    
    int max_sprites_x = SCREEN_WIDTH/SPRITE_DIM;
    int max_sprites_y = SCREEN_HEIGHT/SPRITE_DIM;
    int i, j, x, y, colour;
    
    sprite_t **sprites = calloc(MAX_SPRITES_Y, sizeof(sprite_t *));
    for(i = 0; i < max_sprites_y; i++)
    {
        sprites[i] = calloc(MAX_SPRITES_X, sizeof(sprite_t));
    }
    colour = 0;
    for(i = 0; i < MAX_SPRITES_X; i++)
    {
        for(j = 0; j < MAX_SPRITES_Y; j++)
        {
            sprites[j][i].x = i * SPRITE_DIM;
            sprites[j][i].y = j * SPRITE_DIM;
            sprites[j][i].pixels = calloc(SPRITE_SIZE, sizeof(pixel_t));
            for(x = 0; x < SPRITE_DIM; x++)
            {
                for(y = 0; y < SPRITE_DIM; y++)
                {
                    sprites[j][i].pixels[y*SPRITE_DIM+x].x = x;
                    sprites[j][i].pixels[y*SPRITE_DIM+x].y = y;
                    sprites[j][i].pixels[y*SPRITE_DIM+x].c = colour;
                }
            }
        }
        colour++;
    }
    
    for(j = 0; j < MAX_SPRITES_Y; j++)
    {
        for(i = 0; i < MAX_SPRITES_X; i++)
        {
            draw_sprite(&sprites[j][i]);
        }
    }
    
    for(j = 0; j < MAX_SPRITES_Y; j++)
    {
        for(i = 0; i < MAX_SPRITES_X; i++)
        {
            free(sprites[j][i].pixels);
        }
        free(sprites[j]);
    }
    free(sprites);
}
