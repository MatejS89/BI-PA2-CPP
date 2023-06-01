#pragma once

#include "CVector2D.h"
#include "string"

/**
 * @enum class EMouseButtonState
 * @brief Enumerates the states of the mouse buttons.
 */
enum class EMouseButtonState {
    NONE,
    LEFT_BUTTON_DOWN,
    RIGHT_BUTTON_DOWN,
};

/**
 * @struct SMouseState
 * @brief Represents the position and button state of the mouse.
 */
struct SMouseState {
    CVector2D m_MousePos;
    EMouseButtonState m_ButtonState;
};
