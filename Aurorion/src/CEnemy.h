#pragma once

#include "CEntity.h"
#include "CRigidBody.h"
#include "CCamera.h"
#include "CCollisionHandler.h"
#include <random>

class CEnemy : public CEntity {
public:
    CEnemy(const SParamLoader &params);

    ~CEnemy() override;

    void Draw() override;

    bool Update() override;

    void Save() const override;

private:
    float GenerateRandomNum();

    void RandomJump();

    void PerformJump();

    void ResetJump();

    void EnemyCheckCollision();

    void UpdateHorizontalMovement();

    void UpdateVerticalMovement();

    void HandleHorizontalCollisions();

    void HandleVerticalCollisions();

    const int JUMP_FORCE = 20;
    const int JUMP_TIME = 10;
    const float MOVEMENT_SPEED = 1.5F;
    const int RADIUS = 300;
    const int MAX_HP = 200;
    const int ATTACK_DMG = 1;
    const int ATTACK_RANGE = 30;
    const float ATTACK_DELAY = 200.0F;
    float m_JumpDelay;
    float m_JumpTimer;
    float m_AttackTimer;

    bool IsPlayerInRange();

    void PerformAttack();

    void MoveTowardsPlayer();
};
