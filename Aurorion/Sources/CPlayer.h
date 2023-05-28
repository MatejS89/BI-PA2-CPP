#pragma once

#include "CEntity.h"
#include "CRigidBody.h"


class CPlayer : public CEntity {
public:
    CPlayer(std::shared_ptr<SParamLoader> params);

    void Draw() override;

    bool Update() override;

    void clean() override;

    void HandleInput();

private:
    const int JUMP_FORCE = 10;
    const int JUMP_TIME = 15;
    const int MOVEMENT_SPEED = 3;
    const int MAX_HP = 100;
    const int ATTACK_DMG = 10;
    const int ATTACK_RANGE = 30;
    const float ATTACK_DELAY = 100.0F;
    float m_AttackDelay;
};