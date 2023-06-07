#pragma once

#include "CEntity.h"

using json = nlohmann::json;

/**
 * @class CPlayer
 * @brief The class representing a player entity, derived from CEntity.
 */
class CPlayer : public CEntity {
public:
    CPlayer();

    ~CPlayer() override;

    /**
     * @brief Creates a shared pointer to a new CPlayer instance.
     * @return A shared pointer to the created CPlayer instance.
     * @note Used in the CGameObjectFactory class
     */
    static std::shared_ptr<CGameObject> Create();

    /**
     * @brief Moves the player according to the input. Checks for collisions
     * and deals fall damage if applicable. Manages player attacks, breaking and building of blocks.
     * The attack is performed only when the attack timer runs out.
     * @return True if player is alive, false otherwise.
     */
    bool Update() override;

    /**
     * @brief Loads the player from a JSON object.
     * @param jsonData The JSON data to load from.
     */
    void Load(const json &jsonData) override;

    /**
     * @brief Saves all player data and entity data in a json element.
     * @return Json element with stored data to be processed.
     */
    json Save() const override;

private:
    /**
     * @brief Handles the input by using CInputHandler. Manages movement, attacking,
     * building and breaking blocks.
     */
    void HandleInput();

    /**
     * @brief Checks the collision of the player with the map as well as the enemies.
     */
    void PlayerCheckCollision();

    /**
     * @brief Moves the player on the x axis and checks if a collision occurred.
     */
    void UpdateHorizontalMovement();

    /**
     * @brief Moves the player on the y axis and checks if a collision occurred.
     */
    void UpdateVerticalMovement();

    /**
     * @brief Checks if a collision occurred on the x axis.
     */
    void HandleVerticalCollisions();

    /**
     * @brief Checks if a collision occurred on the y axis.
     */
    void HandleHorizontalCollisions();

    int JUMP_FORCE = 10;

    int JUMP_TIME = 15;

    int MOVEMENT_SPEED = 3;

    int ATTACK_DMG = 200;

    int ATTACK_RANGE = 30;

    float ATTACK_DELAY = 100.0F;

    float m_AttackTimer;
};