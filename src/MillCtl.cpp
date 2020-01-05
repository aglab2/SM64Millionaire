#include "MillCtl.h"
#include <inputs.h>
#include "warp.h"
#include "thirdparty.h"
#include "ColorPads.h"
#include "NumbersInput.h"
#include "NumbersWriter.h"
#include "World.h"
#include "StringFit.hpp"
#include "RainbowColors.h"
#include "Colors.h"
#include "global.h"
#include "Music.h"

#pragma pack(push, 1)
struct AnswerInfo
{
    char txt[63];
    char nofit;
};

struct QuestionInfo
{
    char question[253];
    char musicOverride;
    char nofit;
    char correctAnswer;
    struct AnswerInfo answers[4];
};
#pragma pack(pop)

#define QUESTION_NUMBER bparam1
#define COUNTDOWN_X     Vars[1]
#define COUNTDOWN_Y     Vars[2]

#define DYNAMIC_LETTERS (Children + 6)
#define SONG_ID  Vars[3]
#define SONG_LEN Vars[4]

#define QUESTION_INFOS ((struct QuestionInfo*)(0x8040E000))
#define QUESTION_INFO (&QUESTION_INFOS[QUESTION_NUMBER - 1])
#define QUESTION_CORR (QUESTION_INFO->correctAnswer - 1)

template<typename T, int sz>
static constexpr int size(T(&)[sz])
{
    return sz;
}

static const triplet CoatsPos[] = {
    { -1193, 0, -1110 }, 
    { -446, 0, -1110 }, 
    { 446, 0, -1110 }, 
    { 1193, 0, -1110 },
};

static const struct triplet QuestionPos = { 0, 654, -717 };

static const struct triplet LettersPos[] = {
    { -1193, 190, -886 },
    { -446,  190, -886 }, 
    { 446,   190, -886 }, 
    { 1193,  190, -886 },
};

static const int Collisions[] = { 0x7B, 0x15, 0x29, 0x30 };

enum LifeLines
{
    LL_FIFTYFIFTY = 0,
    LL_AUDIENCE,
    LL_CALLFRIEND,
};

static const int LifelinesCollision[]  = { 0x35, 0x36, 0x37 };

enum Actions
{
    PREPARE,
    UNVEIL,
    PICKING,
    FINAL,
    RESULTS,
    WALKAWAY,

    LIFELINES,
    FIFTYFIFTY = LIFELINES,
    AUDIENCE,
    CALLFRIEND,
    AUDIENCE_PICKING,
    AUDIENCE_PICKINGAFTER,
    CALLFRIEND_CD,
};

void MillCtl::FreezeMario()
{
    M64_MARIO_STRUCT->pos = pos;
}

void MillCtl::MaskInputs(int inputs)
{
    M64_CONTROLLER1_BUTTONS_HOLD  &= ~(inputs);
    M64_CONTROLLER1_BUTTONS_PRESS &= ~(inputs);
}

void MillCtl::SetCamera()
{
    ParallelLakituState = 4;
    ParallelLakituType = 10;
    PickedAngle(10);
}

void MillCtl::SetMusic(int music)
{
    SONG_ID  = music;
    SONG_LEN = 0;
    ::SetMusic(0, music, 0);
}

void MillCtl::SetGamingMusic()
{
    int track = 0;
    if (QUESTION_INFO->musicOverride)
    {
        track = QUESTION_INFO->musicOverride;
    }
    else
    {
        track = Music::GetGameMusic(GetWorld(QUESTION_NUMBER), 
                                    GetLevel(QUESTION_NUMBER));
    }
    SetMusic(track);
}

// culprit :(

static int Culprits[] = { 4700, 4450, 4200, 3950, 3750 };

void MillCtl::FixMusic()
{
    SONG_LEN++;
    if (SONG_ID == Music::MUSIC_P1)
    {
        if (SONG_LEN > 3250)
            SetMusic(SONG_ID);
    }
    if (Music::MUSIC_P2 <= SONG_ID  && SONG_ID <= Music::MUSIC_P4_END)
    {
        if (SONG_LEN > Culprits[GetLevel(QUESTION_NUMBER)])
            SetMusic(SONG_ID);
    }

    //PrintInt(20, 20, "%d", SONG_LEN);
}

void MillCtl::SetWinMusic()
{
    int track = Music::GetWinMusic(GetLevel(QUESTION_NUMBER));
    SetMusic(track);
}

void MillCtl::PrintHint(const char* msg, int offset)
{
    PrintXY(160, 20 + offset, msg);
}

void MillCtl::Init()
{
    Question = QUESTION_NUMBER;

    SetCamera();
    for (int i = 0; i <= 3; i++)
        SetColorAnswer(i, 0xff, 0xff, 0xff);

    for (int i = 0; i < size(CoatsPos); i++)
    {
        Children[i] = SpawnObj(this, MODEL_VEIL, 0x13002A48);
        Children[i]->pos = CoatsPos[i];
    }

    QuestionInfo* info = &QUESTION_INFOS[QUESTION_NUMBER - 1];

    {
        float scale;
        if (info->nofit)
        {
            scale = StringFit::GetOptScale(info->question);
        }
        else
        {
            scale = StringFit::Fit(info->question);
        }

        MObject* obj = SpawnObj(this, MODEL_DYNTEXT, 0x00408018);
        obj->Vars[0] = (int) info->question;
        obj->bparam1 = GetWorld(QUESTION_NUMBER);
        obj->pos = QuestionPos;
        obj->scaling = { scale, scale, scale };
    }

    for (int i = 0; i < 4; i++)
    {
        AnswerInfo* ai = &info->answers[i];
        float scale;
        if (ai->nofit)
            scale = StringFit::GetOptScale(ai->txt);
        else
            scale = StringFit::Fit(ai->txt);

        scale *= 0.61f;

        DYNAMIC_LETTERS[i] = SpawnObj(this, MODEL_DYNTEXT, 0x00408018);
        DYNAMIC_LETTERS[i]->Vars[0] = (int) ai->txt;
        DYNAMIC_LETTERS[i]->bparam1 = GetWorld(QUESTION_NUMBER);
        DYNAMIC_LETTERS[i]->pos = LettersPos[i];
        DYNAMIC_LETTERS[i]->scaling = { scale, scale, scale };
    }
}

void MillCtl::Prepare()
{
    FreezeMario();
    if (QUESTION_NUMBER < 6)
    {
        SetGamingMusic();
        for (int i = 0; i < size(CoatsPos); i++)
            Children[i]->active = 0;
        action = PICKING;
    }
    else
    {
        if (timer == 0)
            SetMusic(Music::MUSIC_LETSPLAY);

        if (timer < 105)
            return;

        SetGamingMusic();
        action = UNVEIL;
    }
}

void MillCtl::PickedAngle(int pick)
{
    if (pick == 0) ParallelLakituAngle =  0x2000;
    if (pick == 1) ParallelLakituAngle =  0x1000;
    if (pick == 2) ParallelLakituAngle = -0x1000;
    if (pick == 3) ParallelLakituAngle = -0x2000;
    if (pick > 3) ParallelLakituAngle =  0;
    MaskInputs(BUTTON_CRIGHT | BUTTON_CLEFT);
}

int MillCtl::GetWorld(int q)
{
    if (q <= 5)  return 0;
    if (q <= 10) return 1;
    if (q < 15)  return 2;
    return 3;
}

int MillCtl::GetLevel(int q)
{
    if (q == 15)
        return 0;
    
    return (q - 1) % 5;
}

void MillCtl::Unveil()
{
    FreezeMario();

    if (subaction < 4)
    {
        PrintHint("Press Start to show");
        if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_START)
        {
            if (!subsubaction)
            {
                Children[subaction]->active = 0;
                subaction++;
                subsubaction = 1;
            }
        }
        else
        {
            subsubaction = 0;
        }
    }
    else
    {
        action = PICKING;
    }

    PickedAngle(subaction-1);
}

void MillCtl::Picking()
{
    for (int i = 0; i < size(Collisions); i++)
        if (M64_MARIO_STRUCT->curr_collision_triangle->collision_type == Collisions[i])
        {
            PrintHint("Start to set final answer");
            if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_START)
            {
                pickedAnswer = i;
                SetColorAnswer(pickedAnswer, 0xFF, 0x7F, 0x00);
                if (QUESTION_NUMBER >= 5)
                {
                    int track = Music::GetFinalMusic(GetLevel(QUESTION_NUMBER));
                    SetMusic(track);
                }

                action = FINAL;
            }
        }
        
    for (int i = 0; i < size(LifelinesCollision); i++)
        if (M64_MARIO_STRUCT->curr_collision_triangle->collision_type == LifelinesCollision[i])
        {
            PrintHint("Start to use lifeline");
            if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_START)
            {
                if (LIFELINES + i != FIFTYFIFTY)
                    SetMusic(Music::MUSIC_AWAIT);
                action = LIFELINES + i;
            }
        }
    
    if (M64_MARIO_STRUCT->curr_collision_triangle->collision_type == 0)
        if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_L)
        {
            SetMusic(0);
            action = WALKAWAY;
        }
}

void MillCtl::Final()
{
    FreezeMario();
    PickedAngle(pickedAnswer);
    if (QUESTION_NUMBER > 5)
    {
        PrintHint("R to show correct");
        if (!(M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_R))
            return;
    }
    
    PickedAngle(QUESTION_CORR);

    SetColorAnswer(pickedAnswer, 0xFF, 0x00, 0x00);
    SetColorAnswer(QUESTION_CORR, 0x00, 0xFF, 0x00);

    DYNAMIC_LETTERS[pickedAnswer]->bparam1 = COLOR_RED;
     
    if (pickedAnswer == QUESTION_CORR)
    {
        DYNAMIC_LETTERS[QUESTION_CORR]->bparam1 = COLOR_RAINBOW;
        SetWinMusic();
    }
    else
    {
        DYNAMIC_LETTERS[QUESTION_CORR]->bparam1 = COLOR_GREEN;
        int track = Music::GetLoseMusic(GetWorld(QUESTION_NUMBER), GetLevel(QUESTION_NUMBER));
        SetMusic(track);
    }

    action = RESULTS;
}

void MillCtl::Results()
{
    NextRainbowColor();
    bool wrongAnswer = pickedAnswer != QUESTION_CORR;

    FreezeMario();
    PickedAngle(QUESTION_CORR);

    PrintHint("L to finish game");
    if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_L)
    {
        if (wrongAnswer)
        {
            State = MS_DEAD;
            SM64Health = 0;
        }
        else
        {
            if (QUESTION_NUMBER == 15)
                State = MS_WIN;

            TriggerWarp(72);
        }
    }
}

void MillCtl::WalkAway()
{
    FreezeMario();
    
    PrintHint("Start to finish game", 20);
    PrintHint("B to cancel");
    if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_START)
    {
        State = MS_QUIT;
        TriggerWarp(69);
    }
    
    if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_B)
    {
        SetGamingMusic();
        action = PICKING;
    }
}

void MillCtl::FiftyFifty()
{
    int answerToLeave;
    do
    {
        answerToLeave = GetRNG() % 4;
    } while (answerToLeave == QUESTION_CORR);
    
    for (int i = 0; i < size(CoatsPos); i++)
    {
        if (i == QUESTION_CORR || i == answerToLeave)
            continue;

        M64_MARIO_STRUCT->pos = pos;
        ParallelLakituAngle = 0;
        
        SetColorAnswer(i, 0x40, 0x40, 0x40);
        MObject* child = SpawnObj(this, MODEL_VEIL, 0x13002A48);
        child->pos = CoatsPos[i];
    }

    action = PICKING;
    PlaySoundProperly(0x2439ff81);
    SetColorLifelines(FIFTYFIFTY - LIFELINES, 0x40, 0x40, 0x40);
}

void MillCtl::Audience()
{
    if (timer == 0)
        NumbersInput::Init();
        
    FreezeMario();
    ParallelLakituAngle = 0;

    PrintHint("Press R to start audience");
    if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_R)
    {
        SetMusic(Music::MUSIC_TIMEOUT);
        action = AUDIENCE_PICKING;
    }
}

void MillCtl::AudiencePicking()
{
    if (timer > 30 * 25)
    {
        SetMusic(Music::MUSIC_AWAIT);
        action = AUDIENCE_PICKINGAFTER;
    }
}

void MillCtl::AudienceAfterPicking()
{
    FreezeMario();
    NumbersInput::Step();

    PrintHint("Press R to finish");
    if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_R)
    {
        MObject* writer = SpawnObj(this, 0, 0x40800C);
        NumbersInput::GetResults(writer->Vars);

        // spawn the things

        SetGamingMusic();
        action = PICKING;
        SetColorLifelines(AUDIENCE - LIFELINES, 0x40, 0x40, 0x40);
    }
}

void MillCtl::CallFriend()
{
    M64_MARIO_STRUCT->pos = pos;
    ParallelLakituAngle = 0;

    PrintHint("Press R to start call");
    if (M64_CONTROLLER1_BUTTONS_PRESS & BUTTON_R)
    {
        SetMusic(Music::MUSIC_TIMEOUT);
        M64_MARIO_STRUCT->pos = pos;
        ParallelLakituAngle = 0;
        action = CALLFRIEND_CD;
    }
}

void MillCtl::CallFriendCountDown()
{
    FreezeMario();
    if (timer % 30 == 0)
    {
        COUNTDOWN_X = 20 + GetRNG() % 260;
        COUNTDOWN_Y = 20 + GetRNG() % 180;
    }

    PrintInt(COUNTDOWN_X + GetRNG() % 5, COUNTDOWN_Y + GetRNG() % 5, "%d", 30 - (timer / 30));

    if (timer == 30 * 30)
    {
        SetGamingMusic();
        action = PICKING;
        SetColorLifelines(CALLFRIEND - LIFELINES, 0x40, 0x40, 0x40);
    }
}

void MillCtl::Step()
{
    GetRNG();
    FixMusic();

    World::Advance();
    switch (action)
    {
        case PREPARE:  
            World::Flashy();
        case AUDIENCE_PICKING:
        case CALLFRIEND_CD:
            World::SlowTremble(GetWorld(QUESTION_NUMBER), (QUESTION_NUMBER - 1) % 5, timer);
        break;

        case WALKAWAY:
        case FINAL:
            break;
        case RESULTS:
        {
        bool wrongAnswer = pickedAnswer != QUESTION_CORR;
            if (!wrongAnswer)
            {
                World::Flashy();
                int maxTime = GetLevel(QUESTION_NUMBER) == 4 ? 200 : 100;
                if (timer < maxTime)
                {
                    World::Tremble(GetWorld(QUESTION_NUMBER), (QUESTION_NUMBER - 1) % 5);
                }
                else
                {
                    World::Wave(GetWorld(QUESTION_NUMBER), (QUESTION_NUMBER - 1) % 5, 20);
                }
            }
        }
        break;
        default:
            World::Wave(GetWorld(QUESTION_NUMBER), (QUESTION_NUMBER - 1) % 5, 20);
        break;
    }

    switch (action)
    {
        case PREPARE:
            Prepare();
        break;
        case UNVEIL:
            Unveil();
        break;
        case PICKING:
            Picking();
        break;
        case FINAL:
            Final();
        break;
        case RESULTS:
            Results();
        break;
        case WALKAWAY:
            WalkAway();
        break;
        case FIFTYFIFTY:
            FiftyFifty();
        break;
        case AUDIENCE:
            Audience();
        break;
        case AUDIENCE_PICKING:
            AudiencePicking();
        break;
        case AUDIENCE_PICKINGAFTER:
            AudienceAfterPicking();
        break;
        case CALLFRIEND:
            CallFriend();
        break;
        case CALLFRIEND_CD:
            CallFriendCountDown();
        break;
    };
    
    MaskInputs(BUTTON_START | BUTTON_CDOWN | BUTTON_CUP | BUTTON_R | BUTTON_DUP | BUTTON_DLEFT | BUTTON_DRIGHT | BUTTON_DDOWN);
}

int MillCtl::Behavior[] =
{
    0x0C000000, (int) sInit,
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,    
};