#pragma once

#include "vector"
#include "memory"
#include "json.hpp"
#include <fstream>

using TileMap = std::vector<std::vector<int>>;

using json = nlohmann::json;

class CMapLayer {
public:
    virtual void LayerRender();

    virtual void LayerUpdate() = 0;

    virtual void SaveMapLayer();

    virtual std::shared_ptr<TileMap> GetTileMap();
};
