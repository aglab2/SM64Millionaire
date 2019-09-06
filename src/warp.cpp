#include "warp.h"

#include <sm64.h>

void TriggerWarp(int id, int type)
{
    // 8024A9CC
    WarpSetUp(M64_MARIO_STRUCT, type);
    // 8033B252
    WarpType = type;
    // 8033B256
    WarpId = id;
}