#pragma once

#include <SDL2/SDL_scancode.h>
#include "CCamera.h"
#include "SMouseState.h"

/**
 * @class CInputHandler
 * @brief Singleton class, handles input events and provides access to input state.
 * The CInputHandler class is responsible for handling input events and providing access to the current input state,
 * such as keyboard and mouse input.
 */
class CInputHandler {
public:
    /**
     * @brief Deleted copy constructor to prevent copying of the input handler object.
     */
    CInputHandler(const CInputHandler &) = delete;

    static CInputHandler &Instance();

    /**
     * @brief Listens for input events.
     * This method listens for input events and updates the state of the mouse and keyboard.
     */
    void Listen();

    /**
     * @brief Checks if a specific key is currently being pressed down.
     * @param key The SDL_Scancode representing the key to check.
     * @return True if the key is currently being pressed down, false otherwise.
     */
    bool IsKeyDown(const SDL_Scancode &key) const;

    /**
     * @brief Retrieves the current mouse position.
     * @return Constant reference to the CVector2D object representing the mouse position.
     */
    const CVector2D &GetMousePos() const;

    /**
     * @brief Retrieves the current state of the mouse button.
     * @return Constant reference to the EMouseButtonState object representing the mouse button state.
     */
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