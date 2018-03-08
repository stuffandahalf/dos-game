#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <sys/nearptr.h>
#include "lib/graphics.h"
#include "lib/input.h"

byte *VGA = (byte *)0xA0000;
word *my_clock = (word *)0x046C;

int main(int argc, char **argv)
{
	setVideoMode(VGA_256_COLOR_MODE);
    VGA+=__djgpp_conventional_base;
    fillScreen(Cyan);
    
    byte c = getKey();
    setVideoMode(TEXT_MODE);
    printf("0x%X\n", c);
	return 0;
}
