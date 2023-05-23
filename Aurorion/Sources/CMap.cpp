#include "CMap.h"

void CMap::MapRender() {
    for (const auto &layer: m_MapLayers) {
        layer->LayerRender();
    }
}

void CMap::MapUpdate() {
    for (const auto &layer: m_MapLayers) {
        layer->LayerUpdate();
    }
}

std::vector<std::shared_ptr<CMapLayer>> CMap::GetMapLayers() const {
    return std::vector<std::shared_ptr<CMapLayer>>();
}

CMap::CMap() {
    
}