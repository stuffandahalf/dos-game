#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <sys/nearptr.h>
#include "graphics.h"
#include "input.h"

byte *VGA = (byte *)0xA0000;
word *my_clock = (word *)0x046C;

int main(int argc, char **argv)
{
	setVideoMode(VGA_256_COLOR_MODE);
    VGA+=__djgpp_conventional_base;
    fillScreen(Cyan);
    //for(int i = 0; i < 99999999; i++);
    
    byte c = getScancode();
    setVideoMode(TEXT_MODE);
    printf("0x%X\n", c);
	return 0;
}
