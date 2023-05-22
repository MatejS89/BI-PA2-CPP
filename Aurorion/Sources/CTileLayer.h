#pragma once

#include "CMapLayer.h"
#include "CTileLayer.h"
#include "STileSet.h"
#include <vector>

using TilesetList = std::vector<STileSet>;

using TileMap = std::vector<std::vector<int>>;

class CTileLayer : public CMapLayer {
public:
    CTileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, const TilesetList &tilesets);

    void LayerRender() override;

    void LayerUpdate() override;

    TileMap GetTileMap() const;

private:
    size_t m_TileSize;
    int m_RowCount;
    int m_ColCount;
    TileMap m_TileMap;
    TilesetList m_TileSets;
};
