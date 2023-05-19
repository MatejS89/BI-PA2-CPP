#include "CGame.h"
#include "CPlayer.h"

SDL_Window *CGame::m_window = nullptr;

SDL_Renderer *CGame::m_renderer = nullptr;

CGame::CGame() {}

CGame::~CGame() {}

CGame CGame::m_instance;

CGame &CGame::Instance() {
    return m_instance;
}

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

        TheTextureManager::Instance().Load
                ("assets/Character/Attack-01/Attack-01-Sheet.png", "attacking", m_renderer);
        TheTextureManager::Instance().Load(
                "assets/Character/Idle/Idle-Sheet.png", "idle", m_renderer
        );

        m_gameObjects.push_back(
                std::make_shared<CPlayer>(std::make_unique<SParamLoader>(100, 100, 96, 82, "attacking")));
        m_gameObjects.push_back(
                std::make_shared<CPlayer>(std::make_unique<SParamLoader>(100, 10, 64, 82, "idle")));
    } else {
        m_isRunning = false;
        return false;
    }
    return true;
}

void CGame::Update() {
    for (const auto &item: m_gameObjects) {
        item->update();
    }
}

void CGame::Render() {
    SDL_RenderClear(m_renderer);
    for (const auto &item: m_gameObjects) {
        item->draw();
    }
    SDL_RenderPresent(m_renderer);
}

void CGame::Clean() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    std::cout << "Game quit and cleaned" << std::endl;
}

bool CGame::Running() {
    return m_isRunning;
}

SDL_Renderer *CGame::GetRenderer() const {
    return m_renderer;
}

void CGame::Quit() {
    m_isRunning = false;
}
