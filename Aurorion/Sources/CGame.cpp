#include "CGame.h"

SDL_Window *CGame::m_window = nullptr;

SDL_Renderer *CGame::m_renderer = nullptr;

CGame::CGame() {}

CGame::~CGame() {}

bool CGame::Init(const std::string &title, int xPos, int yPos, int width, int height, bool fullScreen) {
    int fullscreenFlag = 0;
    if (fullScreen)
        fullscreenFlag = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized" << std::endl;

        m_window = SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, fullscreenFlag);
        if (m_window)
            std::cout << "Window created." << std::endl;
        else
            return false;

        m_renderer = SDL_CreateRenderer(m_window, -1, 0);
        if (m_renderer) {
            SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
            std::cout << "Renderer created." << std::endl;
        } else
            return false;

        m_isRunning = true;
        m_height = height;
        m_width = width;

        m_textureManager.Load
                ("assets/Character/Attack-01/Attack-01-Sheet.png", "animate", m_renderer);
    } else {
        m_isRunning = false;
        return false;
    }

    return true;
}

void CGame::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        m_isRunning = false;
        return;
    }
    if (event.type == SDL_KEYDOWN)
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                break;
            case SDLK_DOWN:
                break;
            case SDLK_RIGHT:
                break;
            case SDLK_LEFT:
                break;
        }
}

void CGame::Update() {
    m_currentFrame = int(((SDL_GetTicks() / 100) % 8));
}

void CGame::Render() {
    SDL_RenderClear(m_renderer);
    m_textureManager.Draw("animate", 0, 0, 96, 80, m_renderer);

    m_textureManager.DrawFrame("animate", 100, 100, 96, 80, 1, m_currentFrame, m_renderer);

    SDL_RenderPresent(m_renderer);
}

void CGame::Clean() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    std::cout << "CGame quit and cleaned" << std::endl;
}

bool CGame::Running() {
    return m_isRunning;
}