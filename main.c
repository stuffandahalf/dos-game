#include <stdio.h>
#include <stdlib.h>
//#include <dos.h>
#include <sys/nearptr.h>

#include "lib/types.h"
#include "lib/graphics.h"
#include "lib/input.h"

byte *VGA = (byte *)0xA0000;
//word *my_clock = (word *)0x046C;

int main(int argc, char **argv)
{
	set_video_mode(VGA_256_COLOR_MODE);
    VGA+=__djgpp_conventional_base;
    
    //colour_test_16();
    
    bool exit = false;
    int x = 0;
    int y = 0;
    colour_t col = Black;
    
    mouse_t m;
    mouse_init(&m);
    
    sprite_t *s = (sprite_t *)malloc(sizeof(sprite_t));
    load_bmp("sprites/test3.bmp", s);
    s->x = SCREEN_WIDTH/2 - s->width/2;
    s->y = SCREEN_HEIGHT/2 - s->height/2;
    draw_sprite(s);
    
    byte c;
    do
    {
        c = get_key_dos();
        //printf("Scancode:\t0x%X\tASCII:\t0x%X\n", c >> 8, c & 0x00FF);
        /*if(c)
        {
            //printf("Character read: 0x%X\n", c);
            printf("Character:\t%c\n", c);
        }*/
        if(c)
        {
            if(!m.available)
            {
                clear_sprite(s);
                //col = rand() % 15 + 1;
                switch(c)
                {
                    case 0x48 :
                        s->y--;
                        break;
                    
                    case 0x4B :
                        s->x--;
                        break;
                        
                    case 0x4D :
                        s->x++;
                        //move_sprite_right(&s);
                        break;
                        
                    case 0x50 :
                        s->y++;
                        break;
                    
                    case 0x1B :
                        exit = true;
                        break;
                }
                fill_screen(Black);
                draw_sprite(s);
            }
            else
            {
                if(c == 0x1B)
                {
                    exit = true;
                }
            }
        }
        if(m.available)
        {
            mouse_update(&m);
            if(s->x != m.x || s->y != m.y)
            {
                clear_sprite(s);
                s->x = m.x;
                s->y = m.y;
                draw_sprite(s);
            }
        }
        
    } while(!exit);
    
    set_video_mode(TEXT_MODE);
    free_sprite(s);
    
	return 0;
}
