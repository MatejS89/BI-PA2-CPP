#pragma once

#include "CEntity.h"
#include "CRigidBody.h"


class CPlayer : public CEntity {
public:
    CPlayer(std::shared_ptr<SParamLoader> params);

    ~CPlayer() override;

    void Draw() override;

    bool Update() override;

    void HandleInput();

    void PlayerCheckCollision();

private:
    const int JUMP_FORCE = 10;
    const int JUMP_TIME = 15;
    const int MOVEMENT_SPEED = 3;
    const int MAX_HP = 100;
    const int ATTACK_DMG = 200;
    const int ATTACK_RANGE = 30;
    const float ATTACK_DELAY = 100.0F;
    float m_AttackDelay;
};