#include "PixelRenderingSystem.h"
#include "Display/Display.h"

void PixelRenderingSystem::Init()
{
    // setup renderer
    auto& renderer2D = Renderer2D::GetInstance();

    m_RenderConnectionID = Renderer2D::GetInstance().GetOnRender2D().Connect([this] (Renderer2D& renderer2D)
    {
        OnRender2D(renderer2D);
    });

    m_PixelViewport = Viewport::GetResourceClass().Load("assets://viewports/pixel.viewport.json");
    m_PixelViewportMaterial = renderer2D.GetDefaultMaterial()->Clone();

    m_PixelViewportMaterial->SetShaderParam("Texture", m_PixelViewport->GetTexture(0));
}

void PixelRenderingSystem::Terminate()
{
    Renderer2D::GetInstance().GetOnRender2D().Disconnect(m_RenderConnectionID);
}

void PixelRenderingSystem::OnRender2D(Renderer2D& renderer2D)
{
    auto& pixelViewportLayer = renderer2D.GetLayer("PixelViewport");

    auto& display = Display::GetInstance();
    Vector2 displaySize(static_cast<float>(display.GetWindowWidth()), static_cast<float>(display.GetWindowHeight()));

    renderer2D.GetLayer("Background").DrawFillRectangle(displaySize, Matrix3x3::IDENTITY(), Color(0.1f, 0.1f, 0.8f, 1.0f));

    Quad2D& quad2D = pixelViewportLayer.DrawQuad2D(m_PixelViewportMaterial);
    quad2D.Create(displaySize, Matrix3x3::IDENTITY(), Color::WHITE(), Vector2(0.0f, 1.0f), Vector2(1.0f, 0.0f));
}
