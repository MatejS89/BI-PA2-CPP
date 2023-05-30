#pragma once

#include <vector>
#include <memory>
#include "CMapLayer.h"

class CMap {
public:
    CMap();

    void MapRender();

    void MapUpdate();

    std::vector<std::shared_ptr<CMapLayer>> GetMapLayers();

    int GetMapWidth() const;

    int GetMapHeight() const;

    void SaveMap();

private:
    std::vector<std::shared_ptr<CMapLayer>> m_MapLayers;

    int m_MapWidth;

    int m_MapHeight;

    friend class CMapParser;
};
