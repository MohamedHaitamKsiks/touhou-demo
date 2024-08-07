#include "ASEngine.h"

#include "Components/Bullet.h"
#include "Components/Player.h"
#include "Components/SpriteRenderer.h"

#include "Systems/DebugRenderingSystem.h"
#include "Systems/PixelRenderingSystem.h"
#include "Systems/PlayerSystem.h"
#include "Systems/BulletSystem.h"
#include "Systems/SpriteRenderingSystem.h"

// module registry for the game
namespace ASEngine
{
    void Registry()
    {
        Module2D::Init();
        AudioModule::Init();

        ASENGINE_REGISTER_COMPONENT(Player);
        ASENGINE_REGISTER_COMPONENT(Bullet);
        ASENGINE_REGISTER_COMPONENT(SpriteRenderer);

        ASENGINE_REGISTER_SYSTEM(PlayerSystem);
        ASENGINE_REGISTER_SYSTEM(PixelRenderingSystem);
        ASENGINE_REGISTER_SYSTEM(BulletSystem);
        ASENGINE_REGISTER_SYSTEM(SpriteRenderingSystem);
        ASENGINE_REGISTER_SYSTEM(DebugRenderingSystem);
    }
} // ASEngine
