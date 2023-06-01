#pragma once

#include "CMapLayer.h"
#include "CTimer.h"
#include "STileSet.h"
#include <random>
#include <vector>
#include "EBlockType.h"

using TilesetList = std::vector<STileSet>;

class CTileLayer : public CMapLayer {
public:
    CTileLayer(int tileSize, int rowCount, int colCount, std::shared_ptr<TileMap> tileMap,
               std::shared_ptr<TilesetList> tilesets);

    void LayerRender() override;

    void LayerUpdate() override;

    void SaveMapLayer() override;

    std::shared_ptr<TileMap> GetTileMap() override;

    int GenerateRandomCoordX() const;

private:
    const float GROW_TIME = 2000.0F;
    size_t m_TileSize;
    int m_RowCount;
    int m_ColCount;
    std::shared_ptr<TileMap> m_TileMap;
    std::shared_ptr<TilesetList> m_TileSets;
    float m_GrowDelay;

    const STileSet &FindTileSet(int tileId) const;
};
