#include "GfxTable.h"

#include <sm64.h>

template<typename T, int sz>
static constexpr int size(T(&)[sz])
{
    return sz;
}

int LetterGfxs[128] = {
    ['A'] = 0x0404A2C0, 
    ['B'] = 0x0404B3D0,
    ['C'] = 0x0404C370,
    ['D'] = 0x0404D240,
    ['E'] = 0x0404E360,
    ['F'] = 0x0404F2C0,
    ['G'] = 0x04050560,
    ['H'] = 0x04051350,
    ['I'] = 0x04052130,
    ['J'] = 0x04053420,
    ['K'] = 0x04054320,
    ['L'] = 0x040551C0,
    ['M'] = 0x040562B0,
    ['N'] = 0x04057250,
    ['O'] = 0x04058280,
    ['P'] = 0x040592F0,
    ['Q'] = 0x0405A390,
    ['R'] = 0x0405B350,
    ['S'] = 0x0405C3F0,
    ['T'] = 0x0405D260,
    ['U'] = 0x0405E2D0,
    ['V'] = 0x0405F1B0,
    ['W'] = 0x04060330,
    ['X'] = 0x04061370,
    ['Y'] = 0x04062290,
    ['Z'] = 0x04063290,

    ['a'] = 0x404AB40,
    ['b'] = 0x404BC40,
    ['c'] = 0x404CB60,
    ['d'] = 0x404DC50,
    ['e'] = 0x404EC50,
    ['f'] = 0x404FC40,
    ['g'] = 0x4064EA0,
    ['h'] = 0x4051B60,
    ['i'] = 0x4052A50,
    ['j'] = 0x4053AE0,
    ['k'] = 0x4054B10,
    ['l'] = 0x40559D0,
    ['m'] = 0x4056AB0,
    ['n'] = 0x4057B60,
    ['o'] = 0x4058B60,
    ['p'] = 0x4059B80,
    ['q'] = 0x405AB70,
    ['r'] = 0x405BAD0,
    ['s'] = 0x405CC00,
    ['t'] = 0x405DC10,
    ['u'] = 0x405EB70,
    ['v'] = 0x405F9B0,
    ['w'] = 0x4060B30,
    ['x'] = 0x4061B70,
    ['y'] = 0x4062A50,
    ['z'] = 0x4063AC0,

    ['\''] = 0x40653B0,
    ['@'] = 0x4066050,
    ['-'] = 0x4066940,
    ['='] = 0x4067250,
    ['!'] = 0x4067B00,
    ['#'] = 0x4068950,
    ['<'] = 0x4069260,
    ['>'] = 0x4069A60,
    ['('] = 0x406A2C0,
    [')'] = 0x406AAE0,
    ['%'] = 0x406B4D0,
    ['.'] = 0x406BA80,
    ['+'] = 0x406C330,
    ['\"'] = 0x406CB70,
    [';'] = 0x406D300,
    ['/'] = 0x406D960,
    ['~'] = 0x406DD20,
    ['_'] = 0x406E040,

    ['0'] = 0x406E490,
    ['1'] = 0x406EAC0,
    ['2'] = 0x406F340,
    ['3'] = 0x406FB40,
    ['4'] = 0x40702B0,
    ['5'] = 0x4070AF0,
    ['6'] = 0x4071470,
    ['7'] = 0x40719B0,
    ['8'] = 0x40726F0,
    ['9'] = 0x4072F10,

    [','] = 0x40733B0,
    [':'] = 0x40738D0,

    ['?'] = 0x040644C0,
};

float LetterSizes[128] = {
    ['A'] = 230, 
    ['B'] = 200,
    ['C'] = 220,
    ['D'] = 210,
    ['E'] = 220,
    ['F'] = 195,
    ['G'] = 245,
    ['H'] = 230,
    ['I'] = 80,
    ['J'] = 175,
    ['K'] = 210,
    ['L'] = 200,
    ['M'] = 312,
    ['N'] = 260,
    ['O'] = 280,
    ['P'] = 220,
    ['Q'] = 275,
    ['R'] = 250,
    ['S'] = 205,
    ['T'] = 200,
    ['U'] = 215,
    ['V'] = 210,
    ['W'] = 320,
    ['X'] = 250,
    ['Y'] = 220,
    ['Z'] = 180,
    
    ['a'] = 200,
    ['b'] = 200,
    ['c'] = 190,
    ['d'] = 190,
    ['e'] = 180,
    ['f'] = 120,
    ['g'] = 190,
    ['h'] = 200,
    ['i'] = 70,
    ['j'] = 60,
    ['k'] = 120,
    ['l'] = 100,
    ['m'] = 300,
    ['n'] = 190,
    ['o'] = 200,
    ['p'] = 170,
    ['q'] = 190,
    ['r'] = 140,
    ['s'] = 160,
    ['t'] = 100,
    ['u'] = 180,
    ['v'] = 190,
    ['w'] = 250,
    ['x'] = 170,
    ['y'] = 170,
    ['z'] = 160,

    ['\''] = 50,
    ['@'] = 330,
    ['-'] = 150,
    ['='] = 170,
    ['!'] = 80,
    ['#'] = 200,
    ['<'] = 200,
    ['>'] = 200,
    ['('] = 110,
    [')'] = 110,
    ['%'] = 270,
    ['.'] = 70,
    ['+'] = 190,
    ['\"'] = 100,
    [';'] = 70,
    ['/'] = 160,
    ['~'] = 200,
    ['_'] = 190,
    
    ['0'] = 190,
    ['1'] = 180,
    ['2'] = 170,
    ['3'] = 160,
    ['4'] = 160,
    ['5'] = 170,
    ['6'] = 170,
    ['7'] = 180,
    ['8'] = 190,
    ['9'] = 180,
    
    [','] = 50,
    [':'] = 70,

    ['?'] = 175,
    [' '] = 230,
};

void SetupGfx()
{
    for (int i = 0; i < size(LetterGfxs); i++)
    {
        int gfxseg = LetterGfxs[i];
        if (!gfxseg)
            continue;

        char* gfx = (char*) SegmentedToVirtual(gfxseg);

        int occurance03 = 0;
        while (occurance03 != 2)
        {
            if (*gfx == 0x03)
            {
                *(int*) (gfx+0) = 0;
                *(int*) (gfx+4) = 0;
                occurance03++;
            }
            gfx += 8;
        }
    }
}