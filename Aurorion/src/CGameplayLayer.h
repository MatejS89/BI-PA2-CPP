#pragma once

#include "CGameLayer.h"
#include "CMap.h"
#include "CHudLayer.h"
#include "CCollisionHandler.h"
#include "CGameObjectFactory.h"
#include "json.hpp"

using json = nlohmann::json;

class CGameplayLayer : public CGameLayer {
public:
    CGameplayLayer();

    void Init(std::shared_ptr<CHudLayer> hud);

    std::shared_ptr<CMap> GetMap() override;

    void DrawLayer() override;

    void UpdateLayer() override;

    void SaveLayer() override;

private:
    int GenerateRandomXCoord() const;

    void SpawnEnemy(json &jsonData);

    const float SPAWN_DELAY = 3000.0F;

    std::shared_ptr<CMap> m_LevelMap;

    json m_EnemyConfig;

    std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>> m_GameObjects;

    float m_SpawnTimer;
};
