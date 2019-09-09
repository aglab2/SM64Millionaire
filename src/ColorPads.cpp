#include "ColorPads.h"
#include <sm64.h>

static int cmdsAnswer[] = { 0x04035FE8, 0x040369B8, 0x04037388, 0x04037D58 };
static int cmdsLifelines[] = { 0x0403AAB8, 0x0403B4B8, 0x0403BEB8 };
static int cmdsWorlds[] = { 0x0403F6D8, 0x04042B48, 0x04045FB8, 0x04049428 };
static int cmdsFlashy = 0x0403C9D8;

static void SetColor(int* cmds, int n, unsigned char r, unsigned char g, unsigned char b)
{
    char* ptr = (char*) SegmentedToVirtual(cmds[n]);
    ptr[4] = r;
    ptr[5] = g;
    ptr[6] = b;
}

void SetColorAnswer(int n, unsigned char r, unsigned char g, unsigned char b)
{
    return SetColor(cmdsAnswer, n, r, g, b);
}

void SetColorLifelines(int n, unsigned char r, unsigned char g, unsigned char b)
{
    return SetColor(cmdsLifelines, n, r, g, b);
}

void SetColorWorlds(int n, unsigned char r, unsigned char g, unsigned char b)
{
    return SetColor(cmdsWorlds, n, r, g, b);
}

void FlashyScroll(int x_off, int y_off)
{
    char* ptr = (char*) SegmentedToVirtual(cmdsFlashy);

    int b1 = ptr[1];
    int b2 = ptr[2];
    int b3 = ptr[3];

    int x = ((b1 << 4) & 0xFF0) | ((b2 >> 4) & 0x00F);
    int y = ((b2 << 4) & 0xF00) | b3;

    x += x_off;
    y += y_off;

    b1 = (x & 0xFF0) >> 4;
    b2 = ((x & 0x00F) << 4) | ((y & 0xF00) >> 8);
    b3 = y & 0xFF;

    ptr[1] = b1;
    ptr[2] = b2;
    ptr[3] = b3;
}