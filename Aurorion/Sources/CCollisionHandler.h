#pragma once

#include "SDL2/SDL.h"
#include <vector>
#include "CTileLayer.h"
#include "CMap.h"
#include "CGame.h"
#include "CInputHandler.h"
#include "CGameObject.h"
#include "CEntity.h"
#include "CEnemy.h"

enum BlockType {
    EMPTY = 0,
    LAVA = 601,
    WATER = 480,
    MUSHROOM = 416,
    DIRT = 53,
};

class CCollisionHandler {
public:
    bool MapCollision(const SDL_Rect &rect, int &hp);

    void LoadCollisionLayer(std::shared_ptr<TileMap> tileLayer);

    bool CheckCollision(const SDL_Rect &left, const SDL_Rect &right) const;

    void LoadGameObjects(std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>>);

    void PlayerAttack(int dmg, int range, const Rotation &rotation);

    void EnemyAttack(int dmg, int range, const Rotation &rotation, const CCollider &col);

    static CCollisionHandler &Instance();

    void DestroyBlock();

    void BuildBlock();

    bool CheckCollisionWithEnemies() const;

    bool CheckCollisionWithPlayer(const CCollider &collider) const;

private:
    CCollisionHandler();

    CVector2D TranslateMouse() const;

    int m_ColCount;

    int m_RowCount;

    int m_TileSize;

    std::shared_ptr<TileMap> m_TileLayer;

    std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>> m_GameObjects;

    static CCollisionHandler m_Instance;
};

typedef CCollisionHandler TheCollisionHandler;
