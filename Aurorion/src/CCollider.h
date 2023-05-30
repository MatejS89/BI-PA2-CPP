#pragma once

#include "SDL2/SDL.h"

class CCollider {
public:
    CCollider();

    CCollider(int x, int y, int w, int h);

    const SDL_Rect &GetCollider() const;

    void SetBuffer(int x, int y, int w, int h);

    void Set(int x, int y, int w, int h);

private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};
