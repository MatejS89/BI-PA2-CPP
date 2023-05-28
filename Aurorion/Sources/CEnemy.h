#pragma once

#include "CEntity.h"
#include "CRigidBody.h"
#include "CCamera.h"
#include "CCollisionHandler.h"
#include <random>


class CEnemy : public CEntity {
public:
    CEnemy(std::shared_ptr<SParamLoader> params);

    void Draw() override;

    bool Update() override;

    void clean() override;

    void RandomJump();

    float GenerateRandomNum();

    void EnemyCheckCollision(const CCollider &collider);

    void FollowPlayer();

private:
    const int JUMP_FORCE = 20;
    const int JUMP_TIME = 10;
    const float MOVEMENT_SPEED = 1.5F;
    const int RADIUS = 300;
    const int MAX_HP = 200;
    const int ATTACK_DMG = 10;
    const int ATTACK_RANGE = 10;
    const float ATTACKDELAY = 200.0F;
    float m_JumpDelay;
    float m_JumpTimer;
    float m_AttackTimer;
};
