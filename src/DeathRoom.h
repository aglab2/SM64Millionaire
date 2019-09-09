#include <sm64.h>

class DeathRoom : public MObject
{
    void Init();
    void Step();

    static void sInit() { reinterpret_cast<DeathRoom*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<DeathRoom*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
    static int Geolayout[];
};