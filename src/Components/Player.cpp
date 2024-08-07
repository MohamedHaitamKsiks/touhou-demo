#include "Player.h"

ASENGINE_SERIALIZE_STRUCT(Player, MaxSpeed, Acceleration, CameraTag, TiltSpeed, TiltAngle, CameraAimOffsetRatio, CameraSmoothing, BulletBuilder, BulletSpeed, BulletCooldown);

void Player::OnCreate(EntityID entityID)
{
    TiltAngle *= Math::PI / 180.0f;

    CameraID = EntityManager::GetInstance().GetEntityByTag(CameraTag);
    Debug::Log(EntityManager::GetInstance().GetTag(entityID).GetString());
}
