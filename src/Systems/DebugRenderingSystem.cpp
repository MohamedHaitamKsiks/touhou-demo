#include "DebugRenderingSystem.h"
#include "2D/Transform2D/Transform2D.h"
#include "Components/SpriteRenderer.h"
#include "Core/Math/Matrix3x3.h"
#include "Core/Math/Vector2.h"
#include "Renderer/Color.h"
#include <sstream>

void DebugRenderingSystem::Init()
{
    // setup renderer
    auto& renderer2D = Renderer2D::GetInstance();

    m_RenderConnectionID = Renderer2D::GetInstance().GetOnRender2D().Connect([this] (Renderer2D& renderer2D)
    {
        OnRender2D(renderer2D);
    });

    m_Font = Font::GetResourceClass().Load("assets://fonts/kongtext_32.font.json");
}

void DebugRenderingSystem::Terminate()
{
    Renderer2D::GetInstance().GetOnRender2D().Disconnect(m_RenderConnectionID);
}

void DebugRenderingSystem::OnRender2D(Renderer2D& renderer2D)
{
    auto& debugLayer = renderer2D.GetLayer("Debug");

    // draw fps
    std::stringstream ssFPS;
    ssFPS << "FPS: " << m_FPS;
    debugLayer.DrawText(m_Font, ssFPS.str(), Matrix3x3::Translate(Vector2(32.0f, 32.0f)), Color::WHITE());

    // draw sprite count
    std::stringstream ssSpriteCount;
    ssSpriteCount << "SpriteCount: " << m_SpriteCount;
    debugLayer.DrawText(m_Font, ssSpriteCount.str(), Matrix3x3::Translate(Vector2(32.0f, 72.0f)), Color::WHITE());
}

void DebugRenderingSystem::Update(float delta)
{
    if (delta > 0.0f)
    {
        m_FPS = (m_FPS * m_FrameCount +  (1.0f / delta)) / (m_FrameCount + 1.0f);
        m_FrameCount += 1.0f;
        if (m_FrameCount > 1000.0f)
            m_FrameCount = 0.0f;
    }

    // count sprites
    m_SpriteCount = 0;

    EntityQuery<SpriteRenderer> query{};
    query.ForEachCollection([this] (ComponentCollection<SpriteRenderer>& sprites, size_t count)
    {
        m_SpriteCount += count;
    });
}
