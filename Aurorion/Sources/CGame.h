#pragma once

#include <iostream>
#include <string>
#include "CTextureManager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class CGame {
public:
    CGame();

    ~CGame();

    bool Init(const std::string &title, int xPos, int yPos, int width, int height, bool fullScreen);

    void HandleEvents();

    void Update();

    void Render();

    void Clean();

    bool Running();

private:
    int m_height;
    int m_width;
    bool m_isRunning;
    static SDL_Window *m_window;
    static SDL_Renderer *m_renderer;
    int m_currentFrame;
};