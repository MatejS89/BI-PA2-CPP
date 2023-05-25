#include "CCollisionHandler.h"
#include "CGame.h"
#include "CTileLayer.h"

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
    if (rightTile > m_ColCount)
        rightTile = m_ColCount;

    if (topTile < 0)
        topTile = 0;

    if (bottomTile > m_RowCount)
        bottomTile = m_RowCount;

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

void CCollisionHandler::LoadCollisionLayer() {
    m_TileLayer = TheGame::Instance().GetMap()->GetMapLayers().front()->GetTileMap();
    m_TileSize = 16;
    m_RowCount = m_TileLayer->size();
    m_ColCount = m_TileLayer->front().size();
}

CCollisionHandler::CCollisionHandler() = default;
