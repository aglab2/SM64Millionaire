#include "RainbowColors.h"

u32 RainbowDarkColor[4] = {
    0x00000000, 0x00000000, 0x28282800, 0x00000000,
};

u32 RainbowLightColor[2] = {
    0x00000000, 0x00000000
};

constexpr int ColorShift = 0x20;
constexpr int MaxColor = (0xFF / ColorShift) * ColorShift;

static unsigned char CurrentRainbowColor[] = {
    MaxColor, ColorShift, 0x00
};

static void SetColors()
{
    int lightColor = CurrentRainbowColor[0] << 24 
                   | CurrentRainbowColor[1] << 16 
                   | CurrentRainbowColor[2] << 8;
    RainbowLightColor[0] = lightColor;
    RainbowLightColor[1] = lightColor;
        
    int darkColor = (CurrentRainbowColor[0] / 2) << 24 
                  | (CurrentRainbowColor[1] / 2) << 16 
                  | (CurrentRainbowColor[2] / 2) << 8;
    RainbowDarkColor[0] = darkColor;
    RainbowDarkColor[1] = darkColor;

}

void NextRainbowColor()
{
    int idxFull;
    for (idxFull = 0; idxFull < 3; idxFull++)
        if (CurrentRainbowColor[idxFull] == MaxColor)
            break;
    
    if (CurrentRainbowColor[(idxFull + 1) % 3] != 0)
    {
        CurrentRainbowColor[(idxFull + 1) % 3] += ColorShift;
        // 2 things are at max color, swap out them
        if (CurrentRainbowColor[(idxFull + 1) % 3] == MaxColor)
        {
            CurrentRainbowColor[(idxFull + 0) % 3] -= ColorShift;
        }
    }
    else
    {
        CurrentRainbowColor[(idxFull + 2) % 3] -= ColorShift;  /*-1=+2*/
        // The previous was ded, start coloring next one
        if (CurrentRainbowColor[(idxFull + 2) % 3] == 0x00)
        {
            CurrentRainbowColor[(idxFull + 1) % 3] += ColorShift;
        }
    }

    SetColors();
}