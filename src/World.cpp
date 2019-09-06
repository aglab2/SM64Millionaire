#include "World.h"

#include <sm64.h>
#include "ColorPads.h"

namespace World
{
    static int Timer;

    void Advance()
    {
        Timer++;
    }

    void Wave(int world, int offset, float amount)
    {
        float fluct = sinf((float) Timer / amount);
        int color = 0xE0 + fluct * 0x1F - offset * 0x20;
        SetColorWorlds(world, color, color, color);
    }

    static int GetFluct(int t)
    {
        if (t < 5)
            return t - 2;
        else
            return 6 - t;
    }
    
    void Flashy()
    {
        if (Timer % 8 == 0)
            FlashyScroll(0, 64);
    }

    void SlowTremble(int world, int offset, int localTimer)
    {
        int fluct = (localTimer / 30) % 2;
        int color = 0xE0 + (fluct * 2 - 1) * 0x1F - offset * 0x20;
        SetColorWorlds(world, color, color, color);
    }

    void Tremble(int world, int offset)
    {
        int fluct = GetFluct(Timer % 8);
        int color = 0xE0 + fluct * 0xF - offset * 0x20;
        SetColorWorlds(world, color, color, color);
    }
}