#include "CGame.h"
#include "CPlayer.h"
#include "CMapParser.h"
#include "CTimer.h"
#include "CCamera.h"
#include <iostream>

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

        TheTextureManager::Instance().AddRenderer(m_renderer);

        m_isRunning = true;
        m_height = height;
        m_width = width;

        TheTextureManager::Instance().Load
                ("assets/Character/Idle/Idle-Sheet.png", "idle");

        if (!TheMapParser::Instance().Load()) {
            std::cout << "FAILED LOAD" << std::endl;
        }

        m_LevelMap = TheMapParser::Instance().GetMaps("MAP");

        std::shared_ptr<CPlayer> player = std::make_shared<CPlayer>(
                std::make_unique<SParamLoader>(100, 100, 64, 80, "idle"));

        TheCamera::Instance().SetTarget(std::shared_ptr<CVector2D>(player->GetCentre()));
        m_gameObjects.push_back(player);
    } else {
        m_isRunning = false;
        return false;
    }
    return true;
}

void CGame::Update() {
    float deltaTime = TheTimer::Instance().GetDeltaTime();
    m_LevelMap->MapUpdate();
    for (const auto &item: m_gameObjects) {
        item->update(deltaTime);
    }
    CCamera::Instance().Update(deltaTime);
}

void CGame::Render() {
    SDL_RenderClear(m_renderer);
    m_LevelMap->MapRender();
    for (const auto &item: m_gameObjects) {
        item->draw();
    }
    SDL_RenderPresent(m_renderer);
}

void CGame::Clean() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    std::cout << "Game quit and cleaned" << std::endl;
}

bool CGame::Running() {
    return m_isRunning;
}

SDL_Renderer *CGame::GetRenderer() {
    return m_renderer;
}

void CGame::Quit() {
    m_isRunning = false;
}

int CGame::GetWindowHeight() const {
    return m_height;
}

int CGame::GetWindowWidth() const {
    return m_width;
}

int CGame::GetMapWidth() const {
    return m_LevelMap->GetMapWidth();
}