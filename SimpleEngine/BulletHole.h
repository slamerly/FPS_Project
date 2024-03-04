#pragma once
#include "Actor.h"

class BulletHole :
    public Actor
{
public:
    BulletHole();

    void updateActor(float dt) override;

private:
    float lifeTime;
};

