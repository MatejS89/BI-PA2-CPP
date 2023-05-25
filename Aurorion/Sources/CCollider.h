#pragma once

#include "SDL2/SDL.h"

class CCollider {
public:

    CCollider(int x, int y, int w, int h);

    const SDL_Rect &GetCollider();

    void SetBuffer(int x, int y, int w, int h);

    void Set(int x, int y, int w, int h);

    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};
