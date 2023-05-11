#pragma once

#include <SDL2/SDL_scancode.h>

class CInputHandler {
public:
    CInputHandler(const CInputHandler &) = delete;

    static CInputHandler &Instance();

    void Listen();

    bool IsKeyDown(SDL_Scancode key);

private:

    CInputHandler();

    void KeyUp();

    void KeyDown();

    const Uint8 *m_KeyStates;

    static CInputHandler m_instance;
};

typedef CInputHandler TheInputHandler;