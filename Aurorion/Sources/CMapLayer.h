#pragma once

#include "vector"
#include "memory"

using TileMap = std::vector<std::vector<int>>;

class CMapLayer {
public:
    virtual void LayerRender() = 0;

    virtual void LayerUpdate() = 0;

    virtual std::shared_ptr<TileMap> GetTileMap() = 0;
};
