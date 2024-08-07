#include "Bullet.h"

ASENGINE_SERIALIZE_STRUCT(Bullet, Velocity, LifeTime);

void Bullet::OnCreate(EntityID entityID)
{
    OwnerID = entityID;
}
