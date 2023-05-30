#pragma once

#include "CEntity.h"
#include "CRigidBody.h"
#include "json.hpp"
#include <fstream>
#include <string>

using json = nlohmann::json;

class CPlayer : public CEntity {
public:
    CPlayer(const SParamLoader &params);

    ~CPlayer() override;

    void Draw() override;

    bool Update() override;

    void Save() const override;

    static std::shared_ptr<CGameObject> Create(const SParamLoader &params);

private:
    const int JUMP_FORCE = 10;
    const int JUMP_TIME = 15;
    const int MOVEMENT_SPEED = 3;
    const int MAX_HP = 100;
    const int ATTACK_DMG = 200;
    const int ATTACK_RANGE = 30;
    const float ATTACK_DELAY = 100.0F;
    float m_AttackDelay;

    void HandleInput();

    void PlayerCheckCollision();

    void UpdateHorizontalMovement();

    void UpdateVerticalMovement();

    void HandleVerticalCollisions();

    json ConvertToJson() const;

    void WriteToJson(const json &jsonData, const std::string &filePath) const;

    void HandleHorizontalCollisions();
};