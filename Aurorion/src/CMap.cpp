#include "CMap.h"

CMap::CMap() = default;

CMap::~CMap() = default;

void CMap::MapRender() {
    for (const auto &layer: m_MapLayers) {
        layer->MapLayerRender();
    }
}

void CMap::MapUpdate() {
    for (const auto &layer: m_MapLayers) {
        layer->MapLayerUpdate();
    }
}

std::vector<std::shared_ptr<CMapLayer>> CMap::GetMapLayers() {
    return m_MapLayers;
}

int CMap::GetMapWidth() const {
    return m_MapWidth;
}

void CMap::SaveMap() {
    for (const auto &layer: m_MapLayers) {
        layer->SaveMapLayer();
    }
}
