#pragma once

#include "CVector2D.h"
#include "string"

enum class EMouseButtonState {
    NONE,
    LEFT_BUTTON_DOWN,
    RIGHT_BUTTON_DOWN,
};

struct SMouseState {
    CVector2D m_MousePos;
    EMouseButtonState m_ButtonState;
};
