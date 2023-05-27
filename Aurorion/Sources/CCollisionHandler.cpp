#include "CCollisionHandler.h"
#include "CGame.h"

CCollisionHandler CCollisionHandler::m_Instance;

bool CCollisionHandler::CheckCollision(const SDL_Rect &left, const SDL_Rect &right) {
    bool x_overlaps = (left.x < right.x + right.w) && (left.x + left.w > right.x);
    bool y_overlaps = (left.y < right.y + right.h) && (left.y + left.h > right.y);
    return (x_overlaps && y_overlaps);
}

bool CCollisionHandler::MapCollision(const SDL_Rect &rect) {
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
            if ((*m_TileLayer)[j][i] > 0) {
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
    m_RowCount = m_TileLayer->size();
    m_ColCount = m_TileLayer->front().size();
}

void CCollisionHandler::DestroyBlock() {
    CVector2D mousePos = TranslateMouse();
    if (mousePos.GetX() >= m_ColCount || mousePos.GetY() >= m_RowCount || mousePos.GetX() < 0 || mousePos.GetY() < 0)
        return;
    if ((*m_TileLayer)[mousePos.GetY()][mousePos.GetX()] > 0) {
        (*m_TileLayer)[mousePos.GetY()][mousePos.GetX()] = 0;
    }
}

void CCollisionHandler::BuildBlock() {
    CVector2D mousePos = TranslateMouse();
    if (mousePos.GetX() >= m_ColCount || mousePos.GetY() >= m_RowCount || mousePos.GetX() < 0 || mousePos.GetY() < 0)
        return;
    if ((*m_TileLayer)[mousePos.GetY()][mousePos.GetX()] == 0) {
        (*m_TileLayer)[mousePos.GetY()][mousePos.GetX()] = 53;
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

CCollisionHandler::CCollisionHandler() = default;
