#pragma once

#include <vector>
#include <memory>
#include "CMapLayer.h"

class CMap {
public:
    CMap();

    void MapRender();

    void MapUpdate();

    std::vector<std::shared_ptr<CMapLayer>> GetMapLayers() const;

private:
    std::vector<std::shared_ptr<CMapLayer>> m_MapLayers;

    friend class CMapParser;
};
