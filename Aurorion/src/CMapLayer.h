#pragma once

#include "vector"
#include "memory"
#include "json.hpp"
#include <fstream>

using TileMap = std::vector<std::vector<int>>;

using json = nlohmann::json;

/**
 * @class CMapLayer
 * @brief Base class for map layers in the game.
 */
class CMapLayer {
public:
    virtual void LayerRender();

    virtual void LayerUpdate() = 0;

    virtual void SaveMapLayer() = 0;

    virtual std::shared_ptr<TileMap> GetTileMap();
};
