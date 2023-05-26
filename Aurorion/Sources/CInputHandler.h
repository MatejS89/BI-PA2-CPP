#pragma once

#include <SDL2/SDL_scancode.h>
#include "CCamera.h"
#include "SMouseState.h"

class CInputHandler {
public:
    CInputHandler(const CInputHandler &) = delete;

    static CInputHandler &Instance();

    void Listen();

    bool IsKeyDown(SDL_Scancode key);

    const CVector2D &GetMousePos() const;

    const EMouseButtonState &GetMouseState() const;

private:
    CInputHandler();

    void KeyUp();

    void KeyDown();

    const Uint8 *m_KeyStates;

    static CInputHandler m_instance;

    SMouseState m_MouseState;
};

typedef CInputHandler TheInputHandler;