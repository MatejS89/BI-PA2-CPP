#pragma once

#include "CMapLayer.h"
#include "CTileLayer.h"
#include "CTimer.h"
#include "STileSet.h"
#include <random>
#include <vector>

using TilesetList = std::vector<STileSet>;

class CTileLayer : public CMapLayer {
public:
    CTileLayer(int tileSize, int rowCount, int colCount, std::shared_ptr<TileMap> tileMap, TilesetList tilesets);

    void LayerRender() override;

    void LayerUpdate() override;

    std::shared_ptr<TileMap> GetTileMap() override;

    int GenerateRandomCoordX() const;

private:
    const float GROW_TIME = 2000.0F;
    size_t m_TileSize;
    int m_RowCount;
    int m_ColCount;
    std::shared_ptr<TileMap> m_TileMap;
    TilesetList m_TileSets;
    float m_GrowDelay;
};
