#include "lib/graphics.h"

extern byte *VGA;

/*void update_sprite(sprite_t *s)
{
    clear_sprite(s);
    draw_sprite(s);
}*/

void move_sprite_right(sprite_t *s)
{
    int i;
    for(i = 0; i < SPRITE_DIM; i++)
    {
        clear_sprite(s);
        s->x++;
        draw_sprite(s);
    }
}

void clear_sprite(sprite_t *s)
{
    int x, y;
    for(y = 0; y < s->height; y++)
    {
        for(x = 0; x < s->width; x++)
        {
            int index = x + y * s->width;
            byte colour = s->data[index];
            if(colour)
            {
                plot_pixel(s->x + x, s->y + y, Black);
            }
        }
    }
}

void draw_sprite(sprite_t *s)
{
    int x, y;
    for(y = 0; y < s->height; y++)
    {
        for(x = 0; x < s->width; x++)
        {
            int index = x + y * s->width;
            byte colour = s->data[index];
            if(colour)
            {
                int pixel_x = s->x + x;
                int pixel_y = s->y + y;
                if(pixel_x >= 0 && pixel_x < SCREEN_WIDTH &&
                    pixel_y >= 0 && pixel_y < SCREEN_HEIGHT)
                {
                    plot_pixel(s->x + x, s->y + y, colour);
                    //printf("0x%X\n", colour);
                }
            }
        }
    }
}

void fill_screen(byte colour)
{
    int x, y;
    for(y = 0; y < SCREEN_HEIGHT; y++)
    {
        for(x = 0; x < SCREEN_WIDTH; x++)
        {
            plot_pixel(x, y, colour);
        }
    }
}

void free_sprite(sprite_t *s)
{
    free(s->data);
    free(s);
}

void colour_test_16()
{
    int i, j, x, y, colour;
    
    sprite_t **sprites = calloc(MAX_SPRITES_Y, sizeof(sprite_t *));
    for(i = 0; i < MAX_SPRITES_Y; i++)
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
            sprites[j][i].data = calloc(SPRITE_DIM * SPRITE_DIM, sizeof(byte));
            for(x = 0; x < SPRITE_DIM; x++)
            {
                for(y = 0; y < SPRITE_DIM; y++)
                {
                    int offset = y * SPRITE_DIM + x;
                    //sprites[j][i].data[offset].x = x;
                    //sprites[j][i].data[offset].y = y;
                    sprites[j][i].data[offset] = colour;
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
            free(sprites[j][i].data);
        }
        free(sprites[j]);
    }
    free(sprites);
}

void fskip(FILE *fp, int num_bytes)
{
    int i;
    for (i = 0; i < num_bytes; i++)
    {
        fgetc(fp);
    }
}

void load_bmp(char *file, sprite_t *s)
{
    s->x = 0;
    s->y = 0;
    
    FILE *fp;
    long index;
    word num_colors;
    int x;

    /* open the file */
    if ((fp = fopen(file,"rb")) == NULL)
    {
        printf("Error opening file %s.\n", file);
        exit(1);
    }

    /* check to see if it is a valid bitmap file */
    if (fgetc(fp) != 'B' || fgetc(fp) != 'M')
    {
        fclose(fp);
        printf("%s is not a bitmap file.\n", file);
        exit(1);
    }

    /* read in the width and height of the image, and the
        number of colors used; ignore the rest */
    fskip(fp, 16);
    fread(&s->width, sizeof(word), 1, fp);
    fskip(fp, 2);
    fread(&s->height, sizeof(word), 1, fp);
    fskip(fp, 22);
    //fskip(fp, 42);
    fread(&num_colors, sizeof(word), 1, fp);
    fskip(fp, 6);

    /* assume we are working with an 8-bit file */
    if(num_colors == 0)
    {
        num_colors = 256;
    }

    /* try to allocate memory */
    if ((s->data = (byte *)malloc((word)(s->width*s->height))) == NULL)
    {
        fclose(fp);
        printf("Error allocating memory for file %s.\n", file);
        exit(1);
    }

    /* Ignore the palette information for now.
        See palette.c for code to read the palette info. */
    fskip(fp, num_colors * 4);

    /* read the bitmap */
    for(index = (s->height - 1) * s->width; index >= 0; index -= s->width)
    {
        for(x=0; x < s->width; x++)
        {
            s->data[(word)index+x] = (byte)fgetc(fp);
        }
    }
    fclose(fp);
}
