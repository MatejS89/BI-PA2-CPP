#include "game.h"
#include "texture_manager.h"
#include "CGameObject.h"
#include "player.h"

CGameObject *objPlayer = nullptr;

CGame::CGame() {}

CGame::~CGame() {}

void CGame::init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen) {
    int fullscreenFlag = 0;
    if (fullScreen)
        fullscreenFlag = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized" << std::endl;

        m_Window = SDL_CreateWindow(title, xPos, yPos, width, height, fullscreenFlag);
        if (m_Window)
            std::cout << "Window created." << std::endl;

        m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
        if (m_Renderer) {
            SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
            std::cout << "Renderer created." << std::endl;
        }
        m_IsRunning = true;
        m_Height = height;
        m_Width = width;
    } else
        m_IsRunning = false;

    CPlayer player("assets/pajko1.png", m_Renderer, 0, 0);
    objPlayer = player.clone();
}

void CGame::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        m_IsRunning = false;
        return;
    }
    if (event.type == SDL_KEYDOWN)
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                objPlayer->move(0);
                break;
            case SDLK_DOWN:
                objPlayer->move(2);
                break;
            case SDLK_RIGHT:
                objPlayer->move(1);
                break;
            case SDLK_LEFT:
                objPlayer->move(3);
                break;
        }
}

void CGame::update() {
    objPlayer->Update();
}

void CGame::render() {
    SDL_RenderClear(m_Renderer);
    objPlayer->Render();
    SDL_RenderPresent(m_Renderer);
}

void CGame::clean() {
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    SDL_Quit();
    std::cout << "CGame quit and cleaned" << std::endl;
}

bool CGame::running() {
    return m_IsRunning;
}