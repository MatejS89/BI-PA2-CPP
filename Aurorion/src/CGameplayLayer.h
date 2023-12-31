#pragma once

#include "CGameLayer.h"
#include "CMap.h"
#include "CHudLayer.h"
#include "CGameObjectFactory.h"

using json = nlohmann::json;

/**
 * @class CGameplayLayer
 * @brief Represents a gameplay layer in the game.
 * The CGameplayLayer class is a derived class of CGameLayer and represents a specific layer
 * responsible for managing gameplay-related elements and interactions.
 */
class CGameplayLayer : public CGameLayer {
public:
    CGameplayLayer();

    ~CGameplayLayer() override;

    /**
     * @brief Initializes the gameplay layer.
     * @param hud A shared pointer to the CHudLayer object,
     * used to add a target of which the hud layer should keep track of.
     * Creates the appropriate GameObjects from the GameObjectData.json file and loads their data.
     */
    void Init(std::shared_ptr<CHudLayer> hud);

    std::shared_ptr<CMap> GetMap() override;

    /**
     * @brief Used to draw the map and game objects on the screen.
     */
    void DrawLayer() override;

    /**
     * @brief Used to update the map and game objects.
     */
    void UpdateLayer() override;

    /**
     * @brief Used to save the map and game objects.
     */
    void SaveLayer() override;

private:
    int GenerateRandomXCoord() const;

    void SpawnNewEnemy();

    void UpdateGameObjects();

    /**
     * @brief Spawns a new enemy.
     * @param jsonData The attributes of the enemy to be spawned.
     */
    void SpawnEnemy(json &jsonData);

    std::shared_ptr<CMap> m_LevelMap;

    const float SPAWN_DELAY = 3000.0F;

    float m_SpawnTimer;

    /**
     * Config used for spawning new enemies.
     */
    json m_EnemyConfig;

    std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>> m_GameObjects;
};
