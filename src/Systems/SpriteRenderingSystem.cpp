#include "SpriteRenderingSystem.h"
#include "2D/Transform2D/Transform2D.h"
#include "Components/SpriteRenderer.h"
#include "Core/Math/Vector2.h"

void SpriteRenderingSystem::Init()
{
    // setup renderer
    auto& renderer2D = Renderer2D::GetInstance();

    m_RenderConnectionID = Renderer2D::GetInstance().GetOnRender2D().Connect([this] (Renderer2D& renderer2D)
    {
        OnRender2D(renderer2D);
    });
}

void SpriteRenderingSystem::Terminate()
{
    Renderer2D::GetInstance().GetOnRender2D().Disconnect(m_RenderConnectionID);
}

void SpriteRenderingSystem::OnRender2D(Renderer2D& renderer2D)
{
    auto& defaultLayer = renderer2D.GetLayer("Default");
    auto& shadowLayer = renderer2D.GetLayer("Shadow");

    EntityQuery<SpriteRenderer, Transform2D> query{};
    query.ForEachCollection([&renderer2D, &defaultLayer, &shadowLayer] (ComponentCollection<SpriteRenderer>& sprites, ComponentCollection<Transform2D>& transforms2D, size_t count)
    {
        for (ComponentIndex i = 0; i < static_cast<ComponentIndex>(count); i++)
        {
            auto& sprite = sprites[i];
            auto& transform2D = transforms2D[i];

            Matrix3x3 globalTransform = transform2D.GetLocalTransform();

            shadowLayer.DrawSprite(sprite.SpriteToRender, Matrix3x3::Translate(Vector2::DOWN() * 4.0f) * globalTransform, sprite.HFrame, sprite.VFrame, Color::BLACK());
            defaultLayer.DrawSprite(sprite.SpriteToRender, globalTransform, sprite.HFrame, sprite.VFrame, Color::WHITE());
        }
    });
}
