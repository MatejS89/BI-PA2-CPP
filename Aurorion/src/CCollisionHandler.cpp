#include "CCollisionHandler.h"

CCollisionHandler CCollisionHandler::m_Instance;

bool CCollisionHandler::CheckCollisionGameObjects(const SDL_Rect &left, const SDL_Rect &right) const {
    bool x_overlaps = (left.x < right.x + right.w) && (left.x + left.w > right.x);
    bool y_overlaps = (left.y < right.y + right.h) && (left.y + left.h > right.y);
    return (x_overlaps && y_overlaps);
}

bool CCollisionHandler::MapCollision(const SDL_Rect &rect, int &hp) {
    int leftTile = rect.x / m_TileSize;
    int rightTile = (rect.x + rect.w) / m_TileSize;
    int topTile = rect.y / m_TileSize;
    int bottomTile = (rect.y + rect.h) / m_TileSize;

    if (leftTile < 0)
        leftTile = 0;
    if (rightTile >= m_ColCount)
        rightTile = m_ColCount - 1;

    if (topTile < 0)
        topTile = 0;

    if (bottomTile >= m_RowCount)
        bottomTile = m_RowCount - 1;

    for (int i = leftTile; i <= rightTile; ++i) {
        for (int j = topTile; j <= bottomTile; ++j) {
            auto &currentTile = (*m_TileLayer)[j][i];
            if (currentTile == LAVA)
                hp -= 1;
            if (currentTile > EMPTY && currentTile != WATER && currentTile != LAVA &&
                currentTile != MUSHROOM) {
                return true;
            }
        }
    }
    return false;
}

CCollisionHandler &CCollisionHandler::Instance() {
    return m_Instance;
}

void CCollisionHandler::LoadCollisionLayer(std::shared_ptr<TileMap> tileLayer) {
    m_TileLayer = tileLayer;
    m_TileSize = 16;
    m_RowCount = tileLayer->size();
    m_ColCount = tileLayer->front().size();
}

void CCollisionHandler::DestroyBlock() {
    CVector2D mousePos = TranslateMouse();
    if (mousePos.GetX() >= m_ColCount || mousePos.GetY() >= m_RowCount || mousePos.GetX() < 0 || mousePos.GetY() < 0)
        return;
    auto &selectedBlock = (*m_TileLayer)[mousePos.GetY()][mousePos.GetX()];
    if (selectedBlock != LAVA && selectedBlock != WATER && selectedBlock != BEDROCK) {
        selectedBlock = EMPTY;
    }
}

void CCollisionHandler::BuildBlock() {
    CVector2D mousePos = TranslateMouse();
    if (mousePos.GetX() >= m_ColCount || mousePos.GetY() >= m_RowCount || mousePos.GetX() < 0 || mousePos.GetY() < 0)
        return;
    auto &selectedBlock = (*m_TileLayer)[mousePos.GetY()][mousePos.GetX()];
    if (selectedBlock == EMPTY ||
        selectedBlock == WATER ||
        selectedBlock == LAVA ||
        selectedBlock == MUSHROOM) {
        selectedBlock = DIRT;
    }
}

CVector2D CCollisionHandler::TranslateMouse() const {
    return CVector2D(floor(
            (TheInputHandler::Instance().GetMousePos().GetX() + TheCamera::Instance().GetPosition().GetX()) /
            m_TileSize), floor(
            (TheInputHandler::Instance().GetMousePos().GetY() + TheCamera::Instance().GetPosition().GetY()) /
            m_TileSize)
    );
}

void CCollisionHandler::LoadGameObjects(std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>> gameObjects) {
    m_GameObjects = gameObjects;
}

bool CCollisionHandler::CheckCollisionWithEnemies() const {
    const auto &player = (*m_GameObjects)[0];
    for (size_t i = 1; i < m_GameObjects->size(); i++) {
        const auto &enemy = (*m_GameObjects)[i];
        if (CheckCollisionGameObjects(player->GetCollider(), enemy->GetCollider()))
            return true;
    }
    return false;
}


void CCollisionHandler::PlayerAttack(int dmg, int range, const Rotation &rotation) {
    const auto &player = (*m_GameObjects)[0];
    CCollider tmp(player->GetCollider().x, player->GetCollider().y, player->GetCollider().w +
                                                                    range, player->GetCollider().h);
    if (rotation == Rotation::LEFT) {
        tmp.Set(tmp.GetCollider().x - range, tmp.GetCollider().y, tmp.GetCollider().w,
                tmp.GetCollider().h);
    }
    for (size_t i = 1; i < m_GameObjects->size(); i++) {
        const auto &enemy = (*m_GameObjects)[i];
        if (CheckCollisionGameObjects(tmp.GetCollider(), enemy->GetCollider()))
            enemy->ReduceHp(dmg);
    }
}

void CCollisionHandler::EnemyAttack(int dmg, int range, const Rotation &rotation, const CCollider &enemy) {
    const auto &player = (*m_GameObjects)[0];
    CCollider tmp(enemy.GetCollider().x, enemy.GetCollider().y, enemy.GetCollider().w +
                                                                range, enemy.GetCollider().h);
    if (rotation == Rotation::RIGHT) {
        tmp.Set(tmp.GetCollider().x - range, tmp.GetCollider().y, tmp.GetCollider().w,
                tmp.GetCollider().h);
    }
    if (CheckCollisionGameObjects(tmp.GetCollider(), player->GetCollider()))
        player->ReduceHp(dmg);
}

bool CCollisionHandler::CheckCollisionWithPlayer(const CCollider &collider) const {
    const auto &player = (*m_GameObjects)[0];
    if (CheckCollisionGameObjects(collider.GetCollider(), player->GetCollider()))
        return true;
    return false;
}

CCollisionHandler::CCollisionHandler() = default;
