#pragma once

#include <ultra/gbi.h>

#ifdef __cplusplus
extern "C"
{
#endif

void *alloc_display_list(u32 size);

void guScale(Mtx* m, float x, float y, float z);
void guRotate(Mtx* m, float a, float x, float y, float z);
void guTranslate(Mtx* m, float, float, float);

#ifdef __cplusplus
}
#endif