#pragma once

#include <iostream>
#include <string>
#include "CTextureManager.h"
#include "CVector2D.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "vector"

class CGameObject;

class CGame {
public:
    ~CGame();

    static CGame *Instance() {
        if (m_instance == nullptr) {
            m_instance = new CGame();
            return m_instance;
        }
        return m_instance;
    }

    bool Init(const std::string &title, int xPos, int yPos, int width, int height, bool fullScreen);

    void HandleEvents();

    void Update();

    void Render();

    void Clean();

    bool Running();

    SDL_Renderer *GetRenderer() const;

private:
    CGame();

    static CGame *m_instance;
    int m_height;
    int m_width;
    bool m_isRunning;
    static SDL_Window *m_window;
    static SDL_Renderer *m_renderer;
    int m_currentFrame;

    std::vector<CGameObject *> m_gameObjects;
};

typedef CGame TheGame;
