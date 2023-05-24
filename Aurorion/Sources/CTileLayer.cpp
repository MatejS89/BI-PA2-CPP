#include "CTileLayer.h"

#include <utility>
#include "CTextureManager.h"
#include "CGame.h"
#include <iostream>

TileMap CTileLayer::GetTileMap() const {
    return m_TileMap;
}

CTileLayer::CTileLayer(int tileSize, int rowCount, int colCount,
                       TileMap tileMap, const TilesetList &tileSets) :
        m_TileSize(tileSize), m_RowCount(rowCount),
        m_ColCount(colCount), m_TileMap(tileMap),
        m_TileSets(tileSets) {
    for (const auto &item: m_TileSets) {
        TheTextureManager::Instance().Load(item.m_TileSetSource, item.m_TileSetName);
    }
}

void CTileLayer::LayerRender() {
    size_t tilesetIndex = 0;
    for (int i = 0; i < m_RowCount; i++) {
        for (int j = 0; j < m_ColCount; j++) {
            int tileId = m_TileMap[i][j];
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
    LayerRender();
}
