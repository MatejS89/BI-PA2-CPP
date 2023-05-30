#include "CGameplayLayer.h"

CGameplayLayer::CGameplayLayer() : m_LevelMap(TheMapParser::Instance().GetMaps("MAP")),
                                   m_gameObjects(std::make_shared<std::vector<std::shared_ptr<CGameObject>>>()) {}

void CGameplayLayer::Init(std::shared_ptr<CHudLayer> hud) {
    std::shared_ptr<CPlayer> player = std::make_shared<CPlayer>(
            SParamLoader(100, 100, 64, 80, "idle"));
    std::shared_ptr<CEnemy> enemy = std::make_shared<CEnemy>(
            SParamLoader(200, 100, 48, 32, "BoarIdle"));
    std::shared_ptr<CEnemy> enemy2 = std::make_shared<CEnemy>(
            SParamLoader(300, 100, 48, 32, "BoarIdle"));
    hud->AddTarget(player);
    TheCamera::Instance().SetTarget(player->GetCentre());
    m_gameObjects->push_back(player);
    m_gameObjects->push_back(enemy);
    m_gameObjects->push_back(enemy2);
    TheCollisionHandler::Instance().LoadGameObjects(m_gameObjects);
    TheCollisionHandler::Instance().LoadCollisionLayer(m_LevelMap->GetMapLayers().back()->GetTileMap());
}

void CGameplayLayer::DrawLayer() {
    m_LevelMap->MapRender();
    for (const auto &item: *m_gameObjects) {
        item->Draw();
    }
}

void CGameplayLayer::UpdateLayer() {
    m_LevelMap->MapUpdate();
    for (size_t i = 0; i < m_gameObjects->size(); i++) {
        if (!(*m_gameObjects)[i]->Update())
            m_gameObjects->erase(m_gameObjects->begin() + i);
    }
}

std::shared_ptr<CMap> CGameplayLayer::GetMap() {
    return m_LevelMap;
}

void CGameplayLayer::SaveLayer() {
    for (const auto &item: *m_gameObjects) {
        item->Save();
    }
    m_LevelMap->SaveMap();
}
