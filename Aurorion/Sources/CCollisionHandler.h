#pragma once

#include "SDL2/SDL.h"
#include <vector>
#include "CTileLayer.h"
#include "CMap.h"
#include "CGame.h"
#include "CInputHandler.h"
#include "CGameObject.h"

class CCollisionHandler {
public:
    bool MapCollision(const SDL_Rect &rect);

    void LoadCollisionLayer(std::shared_ptr<TileMap> tileLayer);

    bool CheckCollision(const SDL_Rect &left, const SDL_Rect &right);

    void LoadGameObjects(std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>>);

    static CCollisionHandler &Instance();

    void DestroyBlock();

    void BuildBlock();

private:
    CCollisionHandler();

    CVector2D TranslateMouse() const;

    int m_ColCount;

    int m_RowCount;

    int m_TileSize;

    std::shared_ptr<TileMap> m_TileLayer;

    std::shared_ptr<CTileLayer> m_CollisionMap;

    std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>> m_GameObjects;

    static CCollisionHandler m_Instance;
};

typedef CCollisionHandler TheCollisionHandler;
