#include "DeathRoom.h"
#include "thirdparty.h"
#include "Colors.h"
#include "global.h"
#include "Scores.h"

static struct triplet DeadPos = { 0, -30, 0 };
static const char DeadText[] = "You Died";
static const char QuitText[] = "You Quit";

static struct triplet ScorePos = { 0, -850, 0 };

static const float Scale = 0.95;

void DeathRoom::Init()
{
    if (State == MS_ALIVE)
    {
        active = 0;
        return;
    }

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
    }

    {
        int score = Question;
        if (State == MS_DEAD)
        {
            if (score >= 10)
                score = 10;
            else if (score >= 5)
                score = 5;
            else
                score = 0;
        }
        else if (State == MS_QUIT)
        {
            score--;
        }
        
        MObject* obj = SpawnObj(this, MODEL_DYNTEXT, 0x00408018);
        obj->Vars[0] = (int) Scores[score];
        obj->bparam1 = COLOR_YELLOW;
        obj->pos = ScorePos;
        obj->scaling = { Scale, Scale, Scale };
    }
}

void DeathRoom::Step()
{
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