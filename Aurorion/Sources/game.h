#pragma once

#include "SDL2/SDL.h"
#include <iostream>
#include "SDL2/SDL_image.h"

class CGame {
public:
    CGame();

    ~CGame();

    void init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen);

    void handleEvents();

    void update();

    void render();

    void clean();

    bool running();

private:
    int m_Height;
    int m_Width;
    bool m_IsRunning;
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
};