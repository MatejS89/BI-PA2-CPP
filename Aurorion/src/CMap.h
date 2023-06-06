#pragma once

#include <vector>
#include <memory>
#include "CMapLayer.h"

/**
 * @class CMap
 * @brief Represents a map consisting of multiple layers.
 */
class CMap {
public:
    CMap();

    ~CMap();

    /**
     * @brief Renders all layers of the map
     */
    void MapRender();

    void MapUpdate();

    std::vector<std::shared_ptr<CMapLayer>> GetMapLayers();

    int GetMapWidth() const;

    void SaveMap();

private:
    std::vector<std::shared_ptr<CMapLayer>> m_MapLayers;

    int m_MapWidth;

    int m_MapHeight;

    friend class CMapParser;
};
