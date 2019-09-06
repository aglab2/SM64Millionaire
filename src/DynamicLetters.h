#include <sm64.h>
#include <ultra/gbi.h>

class DynamicLetters : public MObject
{
    void Init();
    void Step();
    Gfx* Draw(u32 sp50, struct GraphNode *sp54, u32 sp58);

    static void sInit() { reinterpret_cast<DynamicLetters*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<DynamicLetters*>(M64_CURR_OBJ_PTR)->Step(); }
    static Gfx* sDraw(u32 sp50, struct GraphNode *sp54, u32 sp58) { return reinterpret_cast<DynamicLetters*>(M64_GFX_OBJ_PTR)->Draw(sp50, sp54, sp58); }

public:
    static int Behavior[];
    static int Geolayout[];
};