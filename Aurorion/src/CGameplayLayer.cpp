#include "CGameplayLayer.h"

CGameplayLayer::CGameplayLayer() : m_LevelMap(TheMapParser::Instance().GetMaps("MAP")),
                                   m_gameObjects(std::make_shared<std::vector<std::shared_ptr<CGameObject>>>()) {}

void CGameplayLayer::Init(std::shared_ptr<CHudLayer> hud) {
    TheObjectFactory::Instance().RegisterObjects();
//    std::shared_ptr<CPlayer> player = std::make_shared<CPlayer>(
//            SParamLoader(100, 100, 64, 80, "idle"));
//    std::shared_ptr<CEnemy> enemy = std::make_shared<CEnemy>(
//            SParamLoader(200, 100, 48, 32, "BoarIdle"));
//    std::shared_ptr<CEnemy> enemy2 = std::make_shared<CEnemy>(
//            SParamLoader(300, 100, 48, 32, "BoarIdle"));
    std::shared_ptr<CGameObject> plr = TheObjectFactory::Instance().CreateGameObject("CPlayer");
    hud->AddTarget(plr);
    plr->Load(LoadJsonFromFile("examples/NewGame/player2.json"));
    TheCamera::Instance().SetTarget(plr->GetCentre());
    m_gameObjects->push_back(plr);
//    m_gameObjects->push_back(enemy);
//    m_gameObjects->push_back(enemy2);
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
    json gameObjectData;
    for (const auto &item: *m_gameObjects) {
        json gameObject = item->Save();
        if (item == *m_gameObjects->begin())
            gameObjectData["Player"] = gameObject;
    }
    std::ofstream file("examples/NewGame/game_data.json");
    if (file.is_open()) {
        file << gameObjectData.dump(4);
        file.close();
    } else
        throw std::logic_error("Failed to save GameObjects");

    m_LevelMap->SaveMap();
}
