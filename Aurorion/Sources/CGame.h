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
#include "CMap.h"

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

    SDL_Renderer *GetRenderer();

    void Quit();

    int GetWindowWidth() const;

    int GetWindowHeight() const;

    int GetMapWidth() const;

    std::shared_ptr<CMap> GetMap();

private:
    CGame();

    ~CGame();

    static SDL_Renderer *m_renderer;

    static CGame m_instance;
    int m_height;
    int m_width;
    bool m_isRunning;
    static SDL_Window *m_window;
    int m_currentFrame;

    std::shared_ptr<CMap> m_LevelMap;

    std::vector<std::shared_ptr<CGameObject>> m_gameObjects;
};

typedef CGame TheGame;
