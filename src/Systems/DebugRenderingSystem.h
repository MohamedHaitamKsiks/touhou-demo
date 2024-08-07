#ifndef __TOUHOU_DEMO_DEBUG_RENDERING_SYSTEM_H
#define __TOUHOU_DEMO_DEBUG_RENDERING_SYSTEM_H


#include "ASEngine.h"
using namespace ASEngine;

class DebugRenderingSystem: public ISystem
{
private:
    SignalConnectionID m_RenderConnectionID;
    ResourceRef<Font> m_Font{};

    float m_FPS = 0.0f;
    float m_FrameCount = 0.0f;
    size_t m_SpriteCount = 0;

    void Init() override;
    void Terminate() override;
    void Update(float delta) override;

    void OnRender2D(Renderer2D& renderer2D);
};

#endif // __TOUHOU_DEMO_DEBUG_RENDERING_SYSTEM_H
