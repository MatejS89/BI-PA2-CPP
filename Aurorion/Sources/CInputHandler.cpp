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
                TheGame::Instance().Quit();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    std::cout << "LEFT CLICK" << std::endl;
                if (event.button.button == SDL_BUTTON_RIGHT)
                    std::cout << "RIGHT CLICK" << std::endl;
            case SDL_MOUSEMOTION:
                int x;
                int y;
                SDL_GetMouseState(&x, &y);
                m_MousePos.SetX(x + TheCamera::Instance().GetTarget()->GetX());
                m_MousePos.SetY(y + TheCamera::Instance().GetTarget()->GetY());
                std::cout << m_MousePos.GetX() << " " << m_MousePos.GetY() << std::endl;
                break;
            default:
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
