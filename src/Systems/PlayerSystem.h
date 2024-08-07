#ifndef __TOUHOU_DEMO_PLAYER_SYSTEM_H
#define __TOUHOU_DEMO_PLAYER_SYSTEM_H

#include "../Components/Player.h"
#include "ASEngine.h"
using namespace ASEngine;

class PlayerSystem: public ISystem
{
private:
    SignalConnectionID m_RenderConnectionID;
    Vector2 m_MousePosition = Vector2::ZERO();

    void Init() override;
    void Terminate() override;

    void FixedUpdate(float delta) override;
    void Update(float delta) override;

    void OnInputEvent(const InputEvent& event) override;
    void OnKeyboardEvent(const InputEventKeyboard& keyEvent);
    void OnMouseMoveEvent(const InputEventMouseMove& mouseEvent);
    void OnMouseButtonEvent(const InputEventMouseButton& mouseEvent);

    void OnRender2D(Renderer2D& renderer2D);
};

#endif // __TOUHOU_DEMO_PLAYER_SYSTEM_H
