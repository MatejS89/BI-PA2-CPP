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
#include "CGameLayer.h"

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

    void Save();

    SDL_Renderer *GetRenderer();

    void Quit();

    int GetWindowWidth() const;

    int GetWindowHeight() const;

    int GetMapWidth() const;

    int GetMapHeight() const;

    CGameLayer &GetLayer(size_t index);

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

    std::vector<std::shared_ptr<CGameLayer>> m_GameLayers;
};

typedef CGame TheGame;
