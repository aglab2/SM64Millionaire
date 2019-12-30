#include "MillCtl.h"
#include "NumbersWriter.h"
#include "DeathRoom.h"
#include "DynamicLetters.h"
#include "Memes.h"
#include "Fountain.h"

#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (int) obj::Behavior,
#define REGISTER_GEOLAYOUT(obj) 0x02000000, (int) obj::Geolayout,

int _start[] = {
    REGISTER_BEHAVIOR (0x00040000, MillCtl)        // 408000
    REGISTER_BEHAVIOR (0x00040000, NumbersWriter)  // 40800C
    REGISTER_BEHAVIOR (0x00040000, DynamicLetters) // 408018
    REGISTER_GEOLAYOUT(DynamicLetters)             // 408024
    REGISTER_BEHAVIOR (0x00040000, Memes)          // 40802C
    REGISTER_BEHAVIOR (0x00040000, DeathRoom)      // 408038
};