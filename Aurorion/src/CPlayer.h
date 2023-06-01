#pragma once

#include "CEntity.h"
#include "json.hpp"
#include <fstream>
#include <string>
#include "CInputHandler.h"
#include "CCollisionHandler.h"
#include "CTimer.h"

using json = nlohmann::json;

/**
 * @class CPlayer
 * @brief The class representing a player entity, derived from CEntity.
 */
class CPlayer : public CEntity {
public:
    CPlayer();

    ~CPlayer() override;

    bool Update() override;

    void Load(const json &jsonData) override;

    json Save() const override;

    /**
     * @brief Creates a shared pointer to a new CPlayer instance.
     * @return A shared pointer to the created CPlayer instance.
     */
    static std::shared_ptr<CGameObject> Create();

private:
    void HandleInput();

    void PlayerCheckCollision();

    void UpdateHorizontalMovement();

    void UpdateVerticalMovement();

    void HandleVerticalCollisions();

    void HandleHorizontalCollisions();

    int JUMP_FORCE = 10;

    int JUMP_TIME = 15;

    int MOVEMENT_SPEED = 3;

    int ATTACK_DMG = 200;

    int ATTACK_RANGE = 30;
    
    float ATTACK_DELAY = 100.0F;

    float m_AttackTimer;
};