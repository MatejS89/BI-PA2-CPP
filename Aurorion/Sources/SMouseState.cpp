#include "SMouseState.h"

std::string SMouseState::GetMouseButtonState() {
    switch (m_ButtonState) {
        case EMouseButtonState::NONE:
            return "NONE";
        case EMouseButtonState::LEFT_BUTTON_DOWN:
            return "LEFT CLICK";
        case EMouseButtonState::RIGHT_BUTTON_DOWN:
            return "RIGHT CLICK";
    }
    return std::string();
}
