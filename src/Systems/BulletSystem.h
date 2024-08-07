#ifndef __TOUHOU_DEMO_BULLET_SYSTEM_H
#define __TOUHOU_DEMO_BULLET_SYSTEM_H

#include "ASEngine.h"
using namespace ASEngine;

class BulletSystem: public ISystem
{
    SignalConnectionID m_RenderConnectionID;

    void Init() override;
    void Terminate() override;

    void Update(float delta) override;
    void OnRender2D(Renderer2D& renderer2D);
};

#endif // __TOUHOU_DEMO_BULLET_SYSTEM_H
