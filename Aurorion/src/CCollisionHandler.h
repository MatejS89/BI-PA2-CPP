#pragma once

#include <vector>
#include "CTileLayer.h"
#include "CEntity.h"

/**
 * @class CCollisionHandler
 * @brief Singleton class, handles collision detection and response for game objects and the game map.
 */
class CCollisionHandler {
public:
    CCollisionHandler(const CCollisionHandler &other) = delete;

    static CCollisionHandler &Instance();

    /**
     * @brief Checks collision between a SDL_Rect and the game map.
     * @param rect The rectangle to check for collision.
     * @param hp The health points to be modified if a collision with a block that deals damage occurs.
     * @return True if a collision occurred, false otherwise.
     */
    bool MapCollision(const SDL_Rect &rect, int &hp);

    /**
     * @brief Loads the collision layer of the game map.
     * @param tileLayer The tile layer containing collision information.
     */
    void LoadCollisionLayer(std::shared_ptr<TileMap> tileLayer);

    /**
     * @brief Checks collision between two game objects.
     * @param left The bounding box of the left game object.
     * @param right The bounding box of the right game object.
     * @return True if a collision occurred, false otherwise.
     */
    bool CheckCollisionGameObjects(const SDL_Rect &left, const SDL_Rect &right) const;

    /**
     * @brief Loads the game objects for collision detection.
     * @param gameObjects The vector of game objects to be loaded.
     */
    void LoadGameObjects(std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>>);

    /**
     * @brief Handles a player attack.
     * @param dmg The damage inflicted by the attack.
     * @param range The range of the attack.
     * @param rotation The rotation of the attack.
     */
    void PlayerAttack(int dmg, int range, const Rotation &rotation);

    /**
     * @brief Handles an enemy attack.
     * @param dmg The damage inflicted by the attack.
     * @param range The range of the attack.
     * @param rotation The rotation of the attack.
     * @param col The collider of the enemy.
     */
    void EnemyAttack(int dmg, int range, const Rotation &rotation, const CCollider &col);

    /**
     * @brief Calculates the position of the mouse and destroys the desired block
     * This is done by changing the id of the block to EMPTY(see EBlockType.h)
     * @note Blocks of types LAVA, WATER or BEDROCK(see EBlockType.h) cannot be destroyed
     */
    void DestroyBlock();

    /**
     * @brief Calculates the position of the mouse and builds a block in the desired place
     * This is done by changing the id of the block to DIRT(see EBlockType.h)
     * @note Only blocks of types EMPTY, WATER, LAVA or MUSHROOM can be built on.
     */
    void BuildBlock();

    /**
     * @brief Checks collision between the player and enemies.
     * @return True if collision occurs, false otherwise.
     */
    bool CheckCollisionWithEnemies() const;

    /**
     * @brief Checks collision between the player and an enemy.
     * @param collider The collider of enemy to check collision with.
     * @return True if collision occurs, false otherwise.
     */
    bool CheckCollisionWithPlayer(const CCollider &collider) const;

private:
    CCollisionHandler();

    /**
     * @brief Translates mouse coordinates to the game world coordinates.
     * @return The translated mouse coordinates.
     * @note The translated coordinates are based on the current position of the camera.
     */
    CVector2D TranslateMouse() const;

    int m_ColCount;

    int m_RowCount;

    int m_TileSize;

    std::shared_ptr<TileMap> m_TileLayer;

    std::shared_ptr<std::vector<std::shared_ptr<CGameObject>>> m_GameObjects;

    static CCollisionHandler m_Instance;
};

typedef CCollisionHandler TheCollisionHandler;
