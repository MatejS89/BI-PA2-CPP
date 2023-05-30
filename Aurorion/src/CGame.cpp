#include "CGame.h"
#include "CMapParser.h"
#include "CTimer.h"
#include "CCamera.h"
#include <iostream>
#include "CCollisionHandler.h"
#include "CHudLayer.h"
#include "CGameplayLayer.h"

SDL_Window *CGame::m_window = nullptr;

SDL_Renderer *CGame::m_renderer = nullptr;

CGame::CGame() {}

CGame::~CGame() {}

CGame CGame::m_instance;

CGame &CGame::Instance() {
    return m_instance;
}

bool CGame::Init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen) {
    int fullscreenFlag = 0;
    if (fullScreen)
        fullscreenFlag = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cout << "Initialized" << std::endl;
        m_window = SDL_CreateWindow(title, xPos, yPos, width, height, fullscreenFlag);
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
        if (!TheMapParser::Instance().Load()) {
            std::cout << "FAILED LOAD" << std::endl;
        }
        std::shared_ptr<CHudLayer> hud = std::make_shared<CHudLayer>();
        std::shared_ptr<CGameplayLayer> gameplayLayer = std::make_shared<CGameplayLayer>();
        gameplayLayer->Init(hud);
        m_GameLayers.push_back(gameplayLayer);
        m_GameLayers.push_back(hud);
    } else {
        m_isRunning = false;
        return false;
    }
    return true;
}

void CGame::Update() {
    for (const auto &item: m_GameLayers) {
        item->UpdateLayer();
    }
    CCamera::Instance().Update();
}

void CGame::Render() {
    SDL_RenderClear(m_renderer);
    for (const auto &item: m_GameLayers) {
        item->DrawLayer();
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
    return m_GameLayers.front()->GetMap()->GetMapWidth();
}

int CGame::GetMapHeight() const {
    return m_GameLayers[0]->GetMap()->GetMapHeight();
}

void CGame::Save() {
    for (const auto &item: m_GameLayers) {
        item->SaveLayer();
    }
}
