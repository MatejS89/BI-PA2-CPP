#pragma once

#include "CGameLayer.h"
#include "CMap.h"
#include "CGameObject.h"
#include "CMapParser.h"
#include "CPlayer.h"
#include "CEnemy.h"
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
    std::shared_ptr<CMap> m_LevelMap;

    std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>> m_GameObjects;
};
