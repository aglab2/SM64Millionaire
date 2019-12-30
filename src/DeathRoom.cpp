#include "DeathRoom.h"
#include "thirdparty.h"
#include "Colors.h"
#include "global.h"
#include "Scores.h"
#include "RainbowColors.h"
#include "Fountain.h"
#include "Music.h"

static struct triplet DeadPos = { 0, -30, 0 };
static const char DeadText[] = "You Died";
static const char QuitText[] = "You Quit";
static const char WinText[]  = "You Did t";

static struct triplet ScorePos = { 0, -850, 0 };

static const float Scale = 0.95;

void DeathRoom::Init()
{
    if (State == MS_ALIVE)
    {
        active = 0;
        return;
    }

    // The top sign
    {
        MObject* obj = SpawnObj(this, MODEL_DYNTEXT, 0x00408018);

        if (State == MS_DEAD)
        {
            obj->Vars[0] = (int) DeadText;
            obj->bparam1 = COLOR_RED;
            obj->pos = DeadPos;
            obj->scaling = { Scale, Scale, Scale };
        }
        if (State == MS_QUIT)
        {
            obj->Vars[0] = (int) QuitText;
            obj->bparam1 = COLOR_YELLOW;
            obj->pos = DeadPos;
            obj->scaling = { Scale, Scale, Scale };
        }
        if (State == MS_WIN)
        {
            obj->Vars[0] = (int) WinText;
            obj->bparam1 = COLOR_RAINBOW;
            obj->pos = DeadPos;
            obj->scaling = { Scale, Scale, Scale };
        }
    }

    // The score sign
    {
        int score = Question;
        if (State == MS_DEAD)
        {
            if (score > 10)
                score = 10;
            else if (score > 5)
                score = 5;
            else
                score = 0;
        }
        else if (State == MS_QUIT)
        {
            score--;
        }
        else if (State == MS_WIN)
        {
            SetMusic(0, Music::MUSIC_TITLE, 0);
            score = 15;
        }
        
        MObject* obj = SpawnObj(this, MODEL_DYNTEXT, 0x00408018);
        obj->Vars[0] = (int) Scores[score];
        obj->bparam1 = COLOR_YELLOW;
        obj->pos = ScorePos;
        obj->scaling = { Scale, Scale, Scale };
    }

    // The fountain
    if (State == MS_WIN)
    {
        {
            MObject* fountain = SpawnObj(this, 0, (int) Fountain::Behavior & 0xFFFFFF);
            fountain->pos = { 0, -500, -400 };
            fountain->bparam1 = 100;
        }
        {
            MObject* fountain = SpawnObj(this, 0, (int) Fountain::Behavior & 0xFFFFFF);
            fountain->pos = { -900, -1500, -1000 };
            fountain->bparam1 = 150;
        }
        {
            MObject* fountain = SpawnObj(this, 0, (int) Fountain::Behavior & 0xFFFFFF);
            fountain->pos = { 900,  -1500, -1000 };
            fountain->bparam1 = 130;
        }
    }
}

void DeathRoom::Step()
{
    NextRainbowColor();
    if (timer > 100)
    {
       M64_MARIO_STRUCT->pos = pos;
    }
}

int DeathRoom::Behavior[] =
{
    0x0C000000, (int) sInit,
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,    
};