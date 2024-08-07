#ifndef __TOUHOU_DEMO_SPRITE_RENDERER_H
#define __TOUHOU_DEMO_SPRITE_RENDERER_H

#include "ASEngine.h"
using namespace ASEngine;

struct SpriteRenderer: public Component<SpriteRenderer>
{
    ResourceRef<Sprite> SpriteToRender{};
    uint32_t HFrame = 0;
    uint32_t VFrame = 0;

    void OnCreate(EntityID entityID) override {}
    void OnDestroy() override {}
};

#endif // __TOUHOU_DEMO_SPRITE_RENDERER_H
