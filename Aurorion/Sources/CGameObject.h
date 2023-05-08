#pragma once

#include "game.h"

class CGameObject {
public:
    CGameObject(const char *texture, SDL_Renderer *renderer, int x, int y);

    ~CGameObject();

    virtual CGameObject *clone() = 0;

    virtual void move(int dir) = 0;

    virtual void Update();

    void Render();

protected:
    int m_xPos, m_yPos;
    int m_Width, m_Height;

    SDL_Renderer *m_Renderer;
    SDL_Texture *m_ObjTexture;
    SDL_Rect m_srcRect, m_destRect;


    friend class CGame;
};
