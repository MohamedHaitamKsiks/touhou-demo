#include "BulletSystem.h"
#include "../Components/Bullet.h"


void BulletSystem::Init()
{
    m_RenderConnectionID = Renderer2D::GetInstance().GetOnRender2D().Connect([this] (Renderer2D& renderer2D)
    {
        OnRender2D(renderer2D);
    });
}

void BulletSystem::Terminate()
{
    Renderer2D::GetInstance().GetOnRender2D().Disconnect(m_RenderConnectionID);
}

void BulletSystem::Update(float delta)
{
    EntityQuery<Bullet, Transform2D> query{};
    query.ForEachCollection([delta] (ComponentCollection<Bullet>& bullets, ComponentCollection<Transform2D>& transforms2D, size_t count)
    {
        for (ComponentIndex i = 0; i < static_cast<ComponentIndex>(count); i++)
        {
            auto& bullet = bullets[i];
            auto& transform2D = transforms2D[i];

            // bullet timer
            bullet.LifeTime -= delta;
            if (bullet.LifeTime < 0.0f)
            {
                EntityManager::GetInstance().Destroy(bullet.OwnerID);
                bullet.OwnerID = CHUNK_NULL;
                continue;
            }

            // animation
            transform2D.Scale = Interpolation::Linear(transform2D.Scale, Vector2::ONE(), delta * 10.0f);

            // movement
            transform2D.Rotation = -bullet.Velocity.Angle();
            transform2D.Position += bullet.Velocity * delta;
        }
    });
}

void BulletSystem::OnRender2D(Renderer2D& renderer2D)
{
}
