#pragma once

#include "CEntity.h"
#include "CRigidBody.h"
#include "json.hpp"
#include <fstream>
#include <string>

using json = nlohmann::json;

class CPlayer : public CEntity {
public:
    CPlayer();

    ~CPlayer() override;

    bool Update() override;

    void Load(const json &jsonData) override;

    json Save() const override;

    static std::shared_ptr<CGameObject> Create();

private:
    int JUMP_FORCE = 10;
    int JUMP_TIME = 15;
    int MOVEMENT_SPEED = 3;
    int ATTACK_DMG = 200;
    int ATTACK_RANGE = 30;
    float ATTACK_DELAY = 100.0F;
    float m_AttackTimer;

    void HandleInput();

    void PlayerCheckCollision();

    void UpdateHorizontalMovement();

    void UpdateVerticalMovement();

    void HandleVerticalCollisions();

    void HandleHorizontalCollisions();
};