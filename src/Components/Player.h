#ifndef __TOUHOU_DEMO_PLAYER_H
#define __TOUHOU_DEMO_PLAYER_H

#include "ASEngine.h"
using namespace ASEngine;

struct Player: public Component<Player>
{
    // sprite
    float TiltAngle = 0.0f;
    float TiltSpeed = 0.0f;
    // movement
    Vector2 Velocity = Vector2::ZERO();
    float MaxSpeed = 400.0f;
    float Acceleration = 800.0f;
    // camera
    UniqueString CameraTag;
    EntityID CameraID;
    float CameraAimOffsetRatio = 0.3f;
    float CameraSmoothing = 30.0f;
    Vector2 CameraOffset = Vector2::ZERO();
    // shooting
    EntityBuilder BulletBuilder;
    float BulletSpeed = 1000.0f;
    int BulletCount = 1;
    float BulletSpread = 0.0f;
    float BulletCooldown = 0.1f;
    float BulletTimer = 0.0f;
    // input
    bool UpIsPressed = false;
    bool DownIsPressed = false;
    bool RightIsPressed = false;
    bool LeftIsPressed = false;
    bool ShootIsPressed = false;
    Vector2 MouseRelativePosition = Vector2::ZERO();

    void OnCreate(EntityID entityID) override;
    void OnDestroy() override {}
};

#endif // __TOUHOU_DEMO_PLAYER_H
