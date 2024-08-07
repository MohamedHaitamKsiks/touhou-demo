#ifndef __TOUHOU_DEMO_BULLET_H
#define __TOUHOU_DEMO_BULLET_H

#include "ASEngine.h"
using namespace ASEngine;

struct Bullet: public Component<Bullet>
{
    Vector2 Velocity;
    float LifeTime = 100.0f;
    EntityID OwnerID;

    void OnCreate(EntityID entityID) override;
    void OnDestroy() override {}
};

#endif // __TOUHOU_DEMO_BULLET_H
