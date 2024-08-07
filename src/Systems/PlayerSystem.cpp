#include "PlayerSystem.h"
#include "../Components/Bullet.h"

#include <sstream>

#define PRECISION 0.001f

void PlayerSystem::Init()
{
    // setup renderer
    m_RenderConnectionID = Renderer2D::GetInstance().GetOnRender2D().Connect([this] (Renderer2D& renderer2D)
    {
        OnRender2D(renderer2D);
    });

}

void PlayerSystem::Terminate()
{
    Renderer2D::GetInstance().GetOnRender2D().Disconnect(m_RenderConnectionID);
}

void PlayerSystem::FixedUpdate(float delta)
{

}

void PlayerSystem::Update(float delta)
{
    if (delta > 0.0)
    {
        std::stringstream ss;
        ss << 1.0f / delta << "FPS";
        //Debug::Log(ss.str());
        //Display::GetInstance().SetWindowTitle(ss.str());
    }

    // player controls
    EntityQuery<Player, Transform2D> query{};
    query.ForEach([delta, this](Player& player, Transform2D& transform2D)
    {
        // camera control
        auto& camera2D =  EntityManager::GetInstance().GetComponent<Camera2D>(player.CameraID);
        auto& cameraTransform2D = EntityManager::GetInstance().GetComponent<Transform2D>(player.CameraID);
        Vector2 viewportSize(static_cast<float>(camera2D.Target->GetWidth()), static_cast<float>(camera2D.Target->GetHeight()));

        // aim control
        player.MouseRelativePosition = m_MousePosition + cameraTransform2D.Position - transform2D.Position;

        // camera is set between the player and the aim
        Vector2 targetCameraPosition = transform2D.Position + player.MouseRelativePosition * player.CameraAimOffsetRatio - viewportSize * 0.5f;
        cameraTransform2D.Position = Interpolation::Linear(cameraTransform2D.Position, targetCameraPosition, player.CameraSmoothing * delta);

        // shooting
        if (player.ShootIsPressed)
        {
            player.BulletTimer -= delta;
            if (player.BulletTimer < 0.0f)
            {
                // setup builder
                auto& bullet = player.BulletBuilder.GetComponent<Bullet>();
                auto& bulletTransform2D = player.BulletBuilder.GetComponent<Transform2D>();

                for (int i = 0; i < 32; i++)
                {
                    if (player.MouseRelativePosition.LengthSquared() > PRECISION)
                        bullet.Velocity = player.MouseRelativePosition.Normalize() * player.BulletSpeed * Random::Range(0.8f, 1.12f);
                    else
                        bullet.Velocity = Vector2::RIGHT() * player.BulletSpeed;

                    bullet.Velocity += bullet.Velocity.Rotate(0.8f * static_cast<float>(i - 16) / static_cast<float>(32)) +  player.Velocity;

                    bulletTransform2D.Position = transform2D.Position;

                    // create instance
                    EntityManager::GetInstance().Create(player.BulletBuilder);
                }


                // reset booldonw
                player.BulletTimer = player.BulletCooldown;
            }
        }

        // get direction
        Vector2 direction = Vector2::ZERO();
        direction.x = static_cast<float>(player.RightIsPressed) - static_cast<float>(player.LeftIsPressed);
        direction.y = static_cast<float>(player.DownIsPressed) - static_cast<float>(player.UpIsPressed);

        if (direction.LengthSquared() > PRECISION)
            direction = direction.Normalize();

        // accelerate
        Vector2 targetVelocity = direction * player.MaxSpeed;
        player.Velocity = Interpolation::Linear(player.Velocity, targetVelocity, delta * player.Acceleration);

        if ((player.Velocity - targetVelocity).LengthSquared() < PRECISION)
        {
            player.Velocity = targetVelocity;
        }

        // move player
        transform2D.Position += player.Velocity * delta;

        // animate player
        transform2D.Rotation = Interpolation::Linear(transform2D.Rotation, - player.TiltAngle * direction.x, player.TiltSpeed * delta);
    });
}

void PlayerSystem::OnInputEvent(const InputEvent& event)
{
    // keyboard input
    if (event.GetType() == InputEventType::KEYBOARD)
    {
        OnKeyboardEvent(event.Get<InputEventKeyboard>());
    }
    else if (event.GetType() == InputEventType::MOUSE_MOVE)
    {
        OnMouseMoveEvent(event.Get<InputEventMouseMove>());
    }
    else if (event.GetType() == InputEventType::MOUSE_BUTTON)
    {
        OnMouseButtonEvent(event.Get<InputEventMouseButton>());
    }
}

void PlayerSystem::OnKeyboardEvent(const InputEventKeyboard& keyEvent)
{
    EntityQuery<Player> query;
    query.ForEach([&keyEvent, this](Player& player)
    {
        if (keyEvent.Code == Keycode::KEY_W)
        {
            player.UpIsPressed = keyEvent.Pressed;
        }
        else if (keyEvent.Code == Keycode::KEY_A)
        {
            player.LeftIsPressed = keyEvent.Pressed;
        }
        else if (keyEvent.Code == Keycode::KEY_S)
        {
            player.DownIsPressed = keyEvent.Pressed;
        }
        else if (keyEvent.Code == Keycode::KEY_D)
        {
            player.RightIsPressed = keyEvent.Pressed;
        }

    });
}

void PlayerSystem::OnMouseMoveEvent(const InputEventMouseMove& mouseEvent)
{
    EntityQuery<Player, Transform2D> query{};
    query.ForEach([&mouseEvent, this](Player& player, Transform2D& transform2D)
    {
        // get camera transform
        auto& camera2D =  EntityManager::GetInstance().GetComponent<Camera2D>(player.CameraID);

        auto& display = Display::GetInstance();
        Vector2 displaySize(static_cast<float>(display.GetWindowWidth()), static_cast<float>(display.GetWindowHeight()));
        Vector2 viewportSize(static_cast<float>(camera2D.Target->GetWidth()), static_cast<float>(camera2D.Target->GetHeight()));

        m_MousePosition = mouseEvent.Position * viewportSize / displaySize;
    });
}

void PlayerSystem::OnMouseButtonEvent(const InputEventMouseButton& mouseEvent)
{
    EntityQuery<Player> query{};
    query.ForEach([&mouseEvent, this](Player& player)
    {
        if (mouseEvent.Button == MouseButton::LEFT)
        {
            player.ShootIsPressed = mouseEvent.Pressed;
            player.BulletTimer = 0.0f;
        }
    });
}

void PlayerSystem::OnRender2D(Renderer2D& renderer2D)
{
}
