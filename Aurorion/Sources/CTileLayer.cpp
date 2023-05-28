#include "CTileLayer.h"

#include <utility>
#include "CTextureManager.h"
#include "CGame.h"
#include <iostream>

CTileLayer::CTileLayer(int tileSize, int rowCount, int colCount,
                       std::shared_ptr<TileMap> tileMap, TilesetList tileSets) :
        m_TileSize(tileSize), m_RowCount(rowCount),
        m_ColCount(colCount), m_TileMap(std::move(tileMap)),
        m_TileSets(std::move(tileSets)),
        m_GrowDelay(0.0F) {
    for (const auto &item: m_TileSets) {
        TheTextureManager::Instance().Load(item.m_TileSetSource, item.m_TileSetName);
    }
}

void CTileLayer::LayerRender() {
    size_t tilesetIndex = 0;
    for (int i = 0; i < m_RowCount; i++) {
        for (int j = 0; j < m_ColCount; j++) {
            int tileId = (*m_TileMap)[i][j];
            if (tileId == 0)
                continue;
            if (m_TileSets.size() > 1) {
                for (size_t k = 0; k < m_TileSets.size(); k++) {
                    const auto &tileSet = m_TileSets[k];
                    if (tileId >= tileSet.m_FirstID && tileId <= tileSet.m_LastID) {
                        tileId += tileSet.m_TileCount - tileSet.m_LastID;
                        tilesetIndex = k;
                        break;
                    }
                }
            }
            STileSet tileSet = m_TileSets[tilesetIndex];
            int tileRow = tileId / tileSet.m_NumCol;
            int tileCol = tileId - tileRow * tileSet.m_NumCol - 1;

            if (tileId % tileSet.m_NumCol == 0) {
                tileRow--;
                tileCol = tileSet.m_NumCol - 1;
            }

            TheTextureManager::Instance().DrawTile(tileSet.m_TileSetName, tileSet.m_TileSize, j * tileSet.m_TileSize,
                                                   i * tileSet.m_TileSize, tileRow, tileCol, SDL_FLIP_NONE);
        }
    }
}

void CTileLayer::LayerUpdate() {
    if (m_GrowDelay <= 0) {
        m_GrowDelay = GROW_TIME;
        int xCoord = floor(GenerateRandomCoordX() / m_TileSize);
        for (int i = floor(TheGame::Instance().GetMapHeight() / m_TileSize) - 1; i >= 0; i--) {
            auto &currentTile = (*m_TileMap)[i][xCoord];
            if (currentTile == LAVA || currentTile == WATER)
                break;
            if (currentTile == EMPTY) {
                currentTile = 416;
                break;
            }
        }
    } else
        m_GrowDelay -= TheTimer::Instance().GetDeltaTime();
}

std::shared_ptr<TileMap> CTileLayer::GetTileMap() {
    return m_TileMap;
}

int CTileLayer::GenerateRandomCoordX() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, TheGame::Instance().GetMapWidth());
    return distribution(gen);
}
