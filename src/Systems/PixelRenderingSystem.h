#ifndef __TOUHOU_DEMO_PIXEL_REMDERING_SYSTEM_H
#define __TOUHOU_DEMO_PIXEL_REMDERING_SYSTEM_H

#include "ASEngine.h"
using namespace ASEngine;

class PixelRenderingSystem: public ISystem
{
private:
    SignalConnectionID m_RenderConnectionID;
    ResourceRef<Viewport> m_PixelViewport{};
    ResourceRef<Material> m_PixelViewportMaterial{};

    void Init() override;
    void Terminate() override;

    void OnRender2D(Renderer2D& renderer2D);
};

#endif // __TOUHOU_DEMO_PIXEL_REMDERING_SYSTEM_H
