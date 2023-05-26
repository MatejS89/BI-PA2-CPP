#include "CGameplayLayer.h"

CGameplayLayer::CGameplayLayer() : m_LevelMap(TheMapParser::Instance().GetMaps("MAP")) {}

void CGameplayLayer::Init() {
    std::shared_ptr<CPlayer> player = std::make_shared<CPlayer>(
            std::make_unique<SParamLoader>(100, 100, 64, 80, "idle"));
    std::shared_ptr<CEnemy> enemy = std::make_shared<CEnemy>(
            std::make_unique<SParamLoader>(200, 100, 48, 32, "BoarIdle"));
    TheCamera::Instance().SetTarget(player->GetCentre());
    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);
}

void CGameplayLayer::DrawLayer() {
    m_LevelMap->MapRender();
    for (const auto &item: m_gameObjects) {
        item->Draw();
    }
}

void CGameplayLayer::UpdateLayer(float deltaTime) {
    m_LevelMap->MapUpdate();
    for (const auto &item: m_gameObjects) {
        item->Update(deltaTime);
    }
}

std::shared_ptr<CMap> CGameplayLayer::GetMap() {
    return m_LevelMap;
}
