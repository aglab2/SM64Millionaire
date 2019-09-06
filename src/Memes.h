#include <sm64.h>

class Memes : public MObject
{
    void Init();
    void Step();

    void Dorrie();
    void Firsty();

    static void sInit() { reinterpret_cast<Memes*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<Memes*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};