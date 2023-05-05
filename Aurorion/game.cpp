#include "game.h"
#include "texture_manager.h"

Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen) {
    int fullscreenFlag = 0;
    if (fullScreen) {
        fullscreenFlag = SDL_WINDOW_FULLSCREEN;
    }

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

        m_Player = TextureManager::LoadTexture(
                "Legacy-Fantasy - High Forest 2.3/Character/Attack-01/Attack-01-Sheet.png",
                m_Renderer);
    } else
        m_IsRunning = false;
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            m_IsRunning = false;
            break;

        default:
            break;
    }
}

void Game::update() {}

void Game::render() {
    SDL_RenderClear(m_Renderer);
    // Add things to render
    SDL_RenderCopy(m_Renderer, m_Player, NULL, NULL);
    SDL_RenderPresent(m_Renderer);
}

void Game::clean() {
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    SDL_Quit();
    std::cout << "Game quit and cleaned" << std::endl;
}

bool Game::running() {
    return m_IsRunning;
}