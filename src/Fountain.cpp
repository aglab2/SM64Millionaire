#include "Fountain.h"

#include "thirdparty.h"

static float rng()
{
    return GetRandomFloat() - 0.5f;
}

void Fountain::Step()
{
    MObject* particle = SpawnObj(this, MODEL_PARTICLE, (int) FountainParticle::Behavior & 0xFFFFFF);
    particle->speed = { rng() * 50, (float)bparam1, rng() * 50 };
    particle->bparam1 = 5;
    particle->model = GetRNG() % 6;
}

int Fountain::Behavior[] = {
    0x00040000,
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,
};

void FountainParticle::Step()
{
    pos += speed;
    y_rotation2 += 100;
    speed.y -= bparam1;
    if (pos.y < -2000)
        active = 0;
}

int FountainParticle::Behavior[] = {
    0x00040000,
    0x11010001,
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,
};