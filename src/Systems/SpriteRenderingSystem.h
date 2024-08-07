#ifndef __TOUHOU_DEMO_SPRITE_RENDERING_SYSTEM_H
#define __TOUHOU_DEMO_SPRITE_RENDERING_SYSTEM_H

#include "ASEngine.h"
using namespace ASEngine;

class SpriteRenderingSystem: public ISystem
{
private:
    SignalConnectionID m_RenderConnectionID;

    void Init() override;
    void Terminate() override;

    void OnRender2D(Renderer2D& renderer2D);
};

#endif // __TOUHOU_DEMO_SPRITE_RENDERING_SYSTEM_H
