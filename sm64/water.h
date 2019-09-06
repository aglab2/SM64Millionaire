#include <sm64struct.h>

#define M64_WATER_BOX_LIST (*(WaterBoxHeader**) 0x80361184)

struct WaterBox {
     s16 id;
     s16 x1;
     s16 z1;
     s16 x2;
     s16 z2;
     s16 y; // can be altered easily
};

struct WaterBoxHeader
{
     s16 count;
     WaterBox boxes[0]; /*count*/
};
