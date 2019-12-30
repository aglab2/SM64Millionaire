#include "Music.h"

int Music::GetGameMusic(int world, int level)
{
    if (world == 0)
    {
        return MUSIC_P1;
    }
    else if (world == 3) // q15
    {
        return MUSIC_P4;
    }
    else
    {
        return MUSIC_P2 + (world - 1) * 5 + level;
    }
}

int Music::GetFinalMusic(int level)
{
    return MUSIC_FINAL + level;
}

int Music::GetLoseMusic(int world, int level)
{
    if (world == 0)
        return MUSIC_LOSE_NOOB;
    if (world == 1 && level == 4)
        return MUSIC_LOSE_10;
    if (world == 3)
        return MUSIC_LOSE_15;

    return MUSIC_LOSE + level;
}

int Music::GetWinMusic(int level)
{
    return MUSIC_WIN + level;
}