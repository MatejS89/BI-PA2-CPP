#include <SDL2/SDL_events.h>
#include <iostream>
#include "CInputHandler.h"
#include "CGame.h"

CInputHandler::CInputHandler() : m_KeyStates(SDL_GetKeyboardState(nullptr)) {}

CInputHandler CInputHandler::m_instance;

CInputHandler &CInputHandler::Instance() {
    return m_instance;
}

void CInputHandler::Listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                TheGame::Instance().Save();
                TheGame::Instance().Quit();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
            case SDL_MOUSEMOTION:
                int x;
                int y;
                SDL_GetMouseState(&x, &y);
                m_MouseState.m_MousePos.SetX(x);
                m_MouseState.m_MousePos.SetY(y);
//                m_MousePos.SetX(x + TheCamera::Instance().GetTarget()->GetX());
//                m_MousePos.SetY(y + TheCamera::Instance().GetTarget()->GetY());
//                std::cout << m_MouseState.m_MousePos.GetX() << " " << m_MouseState.m_MousePos.GetY()
//                          << m_MouseState.GetMouseButtonState() << std::endl;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
//                    std::cout << "LEFT CLICK" << std::endl;
                    m_MouseState.m_ButtonState = EMouseButtonState::LEFT_BUTTON_DOWN;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
//                    std::cout << "RIGHT CLICK" << std::endl;
                    m_MouseState.m_ButtonState = EMouseButtonState::RIGHT_BUTTON_DOWN;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                m_MouseState.m_ButtonState = EMouseButtonState::NONE;
                break;
        }
    }
}

bool CInputHandler::IsKeyDown(SDL_Scancode key) {
    return m_KeyStates[key];
}

void CInputHandler::KeyUp() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void CInputHandler::KeyDown() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

const CVector2D &CInputHandler::GetMousePos() const {
    return m_MouseState.m_MousePos;
}

const EMouseButtonState &CInputHandler::GetMouseState() const {
    return m_MouseState.m_ButtonState;
}
