#pragma once
#include <sm64.h>

class Fountain : public MObject
{
    void Init();
    void Step();

    static void sInit() { reinterpret_cast<Fountain*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<Fountain*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};

class FountainParticle : public MObject
{
    void Init();
    void Step();

    static void sInit() { reinterpret_cast<FountainParticle*>(M64_CURR_OBJ_PTR)->Init(); }
    static void sStep() { reinterpret_cast<FountainParticle*>(M64_CURR_OBJ_PTR)->Step(); }

public:
    static int Behavior[];
};