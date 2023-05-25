#pragma once

#include "SDL2/SDL.h"
#include <vector>
#include "CTileLayer.h"
#include "CMap.h"
#include "CGame.h"

class CCollisionHandler {
public:
    bool MapCollision(const SDL_Rect &rect);

    void LoadCollisionLayer();

    bool CheckCollision(const SDL_Rect &left, const SDL_Rect &right);

    static CCollisionHandler &Instance();

private:
    CCollisionHandler();

    int m_ColCount;

    int m_RowCount;

    int m_TileSize;

    std::shared_ptr<TileMap> m_TileLayer;

    std::shared_ptr<CTileLayer> m_CollisionMap;

    static CCollisionHandler m_Instance;
};

typedef CCollisionHandler TheCollisionHandler;
