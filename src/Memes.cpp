#include "Memes.h"

#include <inputs.h>

#define PREV_ACT    Vars[0]
#define IS_RED      Vars[1]
#define FIRSTY_CNT  Vars[2]
#define CAN_RED     Vars[3]
#define DORRIE_TIME Vars[4]

void Memes::Init()
{

}

const char* DorriesText[] = { "RIGHTDORRIE"
                            , "LEFTDORRIE"
                            , "COMFYDORRIE"
                            , "YEETDORRIE"
                            , "HIGHDORRIE"
                            , "CRAFTDORRIE"
                            , "CRAFTW"
                            , "AYY LMAO" };

void Memes::Dorrie()
{
    DORRIE_TIME += GetRNG() % 10;
    if (DORRIE_TIME > 3000)
    {
        DORRIE_TIME = 0;
        int idx = sizeof(DorriesText) / sizeof(DorriesText[0]);
        PrintXY(160, 200, DorriesText[GetRNG() % idx]);
    }
}

void Memes::Firsty()
{
    int num = *((int*)0x8033B17C);
    if (num != PREV_ACT)
    {
        if (num != 0x03000886 && num != 0x000008A7)
        {
            if (FIRSTY_CNT != 0 && !IS_RED)
            {
                IS_RED = true;
            }
            else
            {
                IS_RED = false;
                FIRSTY_CNT = 0;
            }
        }
        if (PREV_ACT == 0x000008A7 && num == 0x03000886)
        {
            if (IS_RED)
            {
                IS_RED = false;
                FIRSTY_CNT = 0;
            }
            FIRSTY_CNT++;
        }
        PREV_ACT = num;
    }
    if (IS_RED)
        PrintXY(140, 200, "HECK");

    if (FIRSTY_CNT > 0)
        PrintInt(180, 200, "FIRSTIES %d", FIRSTY_CNT);
}

void Memes::Step()
{
    Firsty();
    Dorrie();
}

int Memes::Behavior[] = {
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,
};