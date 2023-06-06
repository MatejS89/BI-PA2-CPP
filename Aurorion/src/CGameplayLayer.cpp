#include "CGameplayLayer.h"
#include "CMapParser.h"
#include "CCollisionHandler.h"
#include <random>

CGameplayLayer::CGameplayLayer() : m_LevelMap(TheMapParser::Instance().GetMap("MAP")),
                                   m_GameObjects(std::make_shared<std::vector<std::shared_ptr<CGameObject>>>()),
                                   m_SpawnTimer(SPAWN_DELAY) {}

void CGameplayLayer::Init(std::shared_ptr<CHudLayer> hud) {
    TheCollisionHandler::Instance().LoadGameObjects(m_GameObjects);
    TheCollisionHandler::Instance().LoadCollisionLayer(m_LevelMap->GetMapLayers().back()->GetTileMap());
    json jsonData = LoadJsonFromFile(TheGame::Instance().GetSource() + "GameObjectData.json");
    if (jsonData.contains("Player")) {
        std::shared_ptr<CGameObject> plr = TheObjectFactory::Instance().CreateGameObject("Player");
        plr->Load(jsonData["Player"]);
        hud->AddTarget(plr);
        TheCamera::Instance().SetTarget(plr->GetCentre());
        m_GameObjects->insert(m_GameObjects->begin(), plr);
    } else
        throw std::logic_error("Save data corrupted");
    if (jsonData.contains("Enemies") && jsonData["Enemies"].is_array()) {
        for (auto &enemyData: jsonData["Enemies"]) {
            SpawnEnemy(enemyData);
        }
    }
    m_EnemyConfig = LoadJsonFromFile(TheGame::Instance().GetSource() + "EnemyConfig.json");
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
    if (m_SpawnTimer <= 0) {
        m_EnemyConfig["POS_X"] = GenerateRandomXCoord();
        SpawnEnemy(m_EnemyConfig);
        m_SpawnTimer = SPAWN_DELAY;
    } else
        m_SpawnTimer -= TheTimer::Instance().GetDeltaTime();
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

    std::ofstream fileEnemyConfig(TheGame::Instance().GetNextSaveDir() + "EnemyConfig.json");
    if (fileEnemyConfig.is_open()) {
        fileEnemyConfig << m_EnemyConfig.dump(4);
        fileEnemyConfig.close();
    } else
        throw std::logic_error("Failed to save EnemyConfig");

    m_LevelMap->SaveMap();
}

void CGameplayLayer::SpawnEnemy(json &jsonData) {
    int pos_X = jsonData["POS_X"];
    int width = jsonData["WIDTH"];
    if (pos_X + width > m_LevelMap->GetMapWidth())
        jsonData["POS_X"] = m_LevelMap->GetMapWidth() - width;
    std::shared_ptr<CGameObject> enemy = TheObjectFactory::Instance().CreateGameObject("Enemy");
    enemy->Load(jsonData);
    m_GameObjects->push_back(enemy);
}

int CGameplayLayer::GenerateRandomXCoord() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, TheGame::Instance().GetMapWidth());
    return distribution(gen);
}
