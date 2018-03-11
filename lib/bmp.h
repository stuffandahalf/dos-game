#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

typedef struct tagBITMAP              /* the structure for a bitmap. */
{
    word width;
    word height;
    byte *data;
} BITMAP;

void fskip(FILE *fp, int num_bytes);
void load_bmp(char *file, BITMAP *b);

#endif
