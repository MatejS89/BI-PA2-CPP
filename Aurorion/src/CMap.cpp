#include "CMap.h"

CMap::CMap() = default;

CMap::~CMap() = default;

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

std::vector<std::shared_ptr<CMapLayer>> CMap::GetMapLayers() {
    return m_MapLayers;
}

int CMap::GetMapWidth() const {
    return m_MapWidth;
}

void CMap::SaveMap() {
    for (const auto &item: m_MapLayers) {
        item->SaveMapLayer();
    }
}
