#pragma once

#include "CEntity.h"
#include "CRigidBody.h"
#include "CCamera.h"
#include "CCollisionHandler.h"
#include "CPlayer.h"
#include <random>

class CEnemy : public CEntity {
public:
    CEnemy();

    ~CEnemy() override;

    void Draw() override;

    bool Update() override;

    json Save() const override;

    void Load(const json &jsonData) override;

    static std::shared_ptr<CGameObject> Create();

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

    int JUMP_FORCE;
    int JUMP_TIME;
    float MOVEMENT_SPEED;
    int RADIUS;
    int ATTACK_DMG;
    int ATTACK_RANGE;
    float ATTACK_DELAY;
    float m_JumpDelay;
    float m_JumpTimer;
    float m_AttackTimer;

    bool IsPlayerInRange();

    void PerformAttack();

    void MoveTowardsPlayer();
};
