#pragma once

#include "CMapLayer.h"
#include "CTileLayer.h"
#include "STileSet.h"
#include <vector>

using TilesetList = std::vector<STileSet>;

class CTileLayer : public CMapLayer {
public:
    CTileLayer(int tileSize, int rowCount, int colCount, std::shared_ptr<TileMap> tileMap, TilesetList tilesets);

    void LayerRender() override;

    void LayerUpdate() override;

    std::shared_ptr<TileMap> GetTileMap() override;

private:
    size_t m_TileSize;
    int m_RowCount;
    int m_ColCount;
    std::shared_ptr<TileMap> m_TileMap;
    TilesetList m_TileSets;
};
