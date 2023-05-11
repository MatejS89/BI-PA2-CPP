#pragma once

#include <iostream>
#include <string>
#include "CTextureManager.h"
#include "CVector2D.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "vector"
#include "CInputHandler.h"
#include "memory"

class CGameObject;

class CGame {
public:
    static CGame &Instance();

    CGame(const CGame &other) = delete;

    bool Init(const std::string &title, int xPos, int yPos, int width, int height, bool fullScreen);

    void Update();

    void Render();

    void Clean();

    bool Running();

    SDL_Renderer *GetRenderer() const;

    void Quit();

private:
    CGame();

    ~CGame();

    static CGame m_instance;
    int m_height;
    int m_width;
    bool m_isRunning;
    static SDL_Window *m_window;
    static SDL_Renderer *m_renderer;
    int m_currentFrame;

    std::vector<std::shared_ptr<CGameObject>> m_gameObjects;
};

typedef CGame TheGame;
