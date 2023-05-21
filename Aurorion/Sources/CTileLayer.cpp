#include "CTileLayer.h"

#include <utility>

TileMap CTileLayer::GetTileMap() const {
    return m_TileMap;
}

CTileLayer::CTileLayer(int tileSize, int rowCount, int colCount,
                       TileMap tileMap, TilesetList tileSets) :
        m_TileSize(tileSize), m_RowCount(rowCount),
        m_ColCount(colCount), m_TileMap(std::move(tileMap)),
        m_TileSets(std::move(tileSets)) {}

void CTileLayer::LayerRender() {
}

void CTileLayer::LayerUpdate() {
}
