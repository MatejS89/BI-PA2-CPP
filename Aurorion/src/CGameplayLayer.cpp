#include "CGameplayLayer.h"

CGameplayLayer::CGameplayLayer() : m_LevelMap(TheMapParser::Instance().GetMaps("MAP")),
                                   m_gameObjects(std::make_shared<std::vector<std::shared_ptr<CGameObject>>>()) {}

void CGameplayLayer::Init(std::shared_ptr<CHudLayer> hud) {
    json jsonData = LoadJsonFromFile(TheGame::Instance().GetSource() + "GameObjectData.json");
    if (jsonData.contains("Player")) {
        std::shared_ptr<CGameObject> plr = TheObjectFactory::Instance().CreateGameObject("Player");
        hud->AddTarget(plr);
        plr->Load(jsonData["Player"]);
        TheCamera::Instance().SetTarget(plr->GetCentre());
        m_gameObjects->insert(m_gameObjects->begin(), plr);
    }
    if (jsonData.contains("Enemies") && jsonData["Enemies"].is_array()) {
        for (const auto &enemyData: jsonData["Enemies"]) {
            std::shared_ptr<CGameObject> enemy = TheObjectFactory::Instance().CreateGameObject("Enemy");
            enemy->Load(enemyData);
            m_gameObjects->push_back(enemy);
        }
    }
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
        if (!(*m_gameObjects)[i]->Update()) {
            m_gameObjects->erase(m_gameObjects->begin() + i);
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
    for (const auto &item: *m_gameObjects) {
        json gameObject = item->Save();
        if (item == *m_gameObjects->begin()) {
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
