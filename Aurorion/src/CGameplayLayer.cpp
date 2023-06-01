#include "CGameplayLayer.h"

CGameplayLayer::CGameplayLayer() : m_LevelMap(TheMapParser::Instance().GetMap("MAP")),
                                   m_GameObjects(std::make_shared<std::vector<std::shared_ptr<CGameObject>>>()) {}

void CGameplayLayer::Init(std::shared_ptr<CHudLayer> hud) {
    json jsonData = LoadJsonFromFile(TheGame::Instance().GetSource() + "GameObjectData.json");
    if (jsonData.contains("Player")) {
        std::shared_ptr<CGameObject> plr = TheObjectFactory::Instance().CreateGameObject("Player");
        hud->AddTarget(plr);
        plr->Load(jsonData["Player"]);
        TheCamera::Instance().SetTarget(plr->GetCentre());
        m_GameObjects->insert(m_GameObjects->begin(), plr);
    }
    if (jsonData.contains("Enemies") && jsonData["Enemies"].is_array()) {
        for (const auto &enemyData: jsonData["Enemies"]) {
            std::shared_ptr<CGameObject> enemy = TheObjectFactory::Instance().CreateGameObject("Enemy");
            enemy->Load(enemyData);
            m_GameObjects->push_back(enemy);
        }
    }
    TheCollisionHandler::Instance().LoadGameObjects(m_GameObjects);
    TheCollisionHandler::Instance().LoadCollisionLayer(m_LevelMap->GetMapLayers().back()->GetTileMap());
}

void CGameplayLayer::DrawLayer() {
    m_LevelMap->MapRender();
    for (const auto &item: *m_GameObjects) {
        item->Draw();
    }
}

void CGameplayLayer::UpdateLayer() {
    m_LevelMap->MapUpdate();
    for (size_t i = 0; i < m_GameObjects->size(); i++) {
        if (!(*m_GameObjects)[i]->Update()) {
            m_GameObjects->erase(m_GameObjects->begin() + i);
            if (i == 0)
                TheGame::Instance().Quit();
        }

    }
}

std::shared_ptr<CMap> CGameplayLayer::GetMap() {
    return m_LevelMap;
}

void CGameplayLayer::SaveLayer() {
    json gameObjectData;
    json enemyData = json::array();
    for (const auto &item: *m_GameObjects) {
        json gameObject = item->Save();
        if (item == *m_GameObjects->begin()) {
            gameObjectData["Player"] = gameObject;
        } else {
            enemyData.push_back(gameObject);
        }
    }
    gameObjectData["Enemies"] = enemyData;
    std::ofstream file(TheGame::Instance().GetNextSaveDir() + "GameObjectData.json");
    if (file.is_open()) {
        file << gameObjectData.dump(4);
        file.close();
    } else
        throw std::logic_error("Failed to save GameObjects");

    m_LevelMap->SaveMap();
}
