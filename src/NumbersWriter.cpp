#include "NumbersWriter.h"
#include "thirdparty.h"

static const struct triplet AudienceVisual[] = {
    { -1190, 30, -880 },
    { -450,  30, -880 }, 
    { 450,   30, -880 }, 
    { 1190,  30, -880 },
};

void NumbersWriter::Init()
{
    float totalCount = 0;
    for (int i = 0; i < 4; i++)
        totalCount += Vars[i];
    
    for (int i = 0; i < 4; i++)
    {
        float scale = ((float) Vars[i]) / totalCount;

        MObject* obj = SpawnObj(this, MODEL_AUDIENCE, 0x13002A48);
        obj->pos = AudienceVisual[i];
        obj->scaling = { scale, 1, 1 };
    }
}

void NumbersWriter::Step()
{
    for (int i = 0; i < 4; i++)
    {
        char str[] = "A %d";
        str[0] += i;
        PrintInt(20, 100 - 20 * i, str, Vars[i]);
    }
}

int NumbersWriter::Behavior[] = {
    0x0C000000, (int) sInit,
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,    
};