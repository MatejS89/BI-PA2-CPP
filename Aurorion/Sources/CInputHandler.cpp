#include <SDL2/SDL_events.h>
#include <iostream>
#include "CInputHandler.h"
#include "CGame.h"

CInputHandler *CInputHandler::m_instance = nullptr;

CInputHandler::CInputHandler() : m_KeyStates(SDL_GetKeyboardState(nullptr)) {}

CInputHandler *CInputHandler::Instance() {
    if (m_instance == nullptr) {
        m_instance = new CInputHandler();
        return m_instance;
    }
    return m_instance;
}

void CInputHandler::Listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                TheGame::Instance()->Quit();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
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
