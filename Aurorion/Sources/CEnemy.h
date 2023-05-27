#pragma once

#include "CEntity.h"
#include "CRigidBody.h"
#include "CCamera.h"
#include <random>


class CEnemy : public CEntity {
public:
    CEnemy(std::shared_ptr<SParamLoader> params);

    void Draw() override;

    bool Update(float deltaTime) override;

    void clean() override;

    void RandomJump(float deltaTime);

    float GenerateRandomNum();

    void FollowPlayer();

private:
    const int JUMP_FORCE = 20;
    const int JUMP_TIME = 10;
    const float MOVEMENT_SPEED = 1.5F;
    const int RADIUS = 200;
    const int MAX_HP = 200;
    float m_JumpDelay;
    float m_JumpTimer;
};
