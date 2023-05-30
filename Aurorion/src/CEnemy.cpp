#include "CEnemy.h"
#include "CTimer.h"

CEnemy::CEnemy() : CEntity(), m_JumpDelay(0.0F),
                   m_JumpTimer(JUMP_TIME), m_AttackTimer(0.0F) {
    m_Collider.SetBuffer(0, 0, 7, 2);
    TheTextureManager::Instance().Load
            ("assets/Mob/Boar/Idle/Idle-Sheet.png", "BoarIdle");
    m_MaxHP = MAX_HP;
    m_CurrHP = MAX_HP;
}

void CEnemy::Draw() {
    CEntity::Draw();
}

bool CEnemy::Update() {
    m_currentFrame = (SDL_GetTicks() / 100) % 4;
    RandomJump();
    if (IsPlayerInRange()) {
        MoveTowardsPlayer();
        PerformAttack();
    } else {
        m_RigidBody->UnsetForce();
    }
    EnemyCheckCollision();
    return CEntity::Update();
}

float CEnemy::GenerateRandomNum() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(100.0F, 200.0F);
    return distribution(gen);
}

void CEnemy::RandomJump() {
    if (m_JumpDelay <= 0 && m_IsGrounded) {
        PerformJump();
    } else if (m_IsGrounded) {
        m_JumpDelay -= TheTimer::Instance().GetDeltaTime();
    }
    if (m_IsJumping && m_JumpTimer > 0.0F)
        m_JumpTimer -= TheTimer::Instance().GetDeltaTime();
    else if (m_JumpTimer <= 0.0F)
        ResetJump();
}

bool CEnemy::IsPlayerInRange() {
    float distanceToPlayer = abs(TheCamera::Instance().GetTarget()->GetX() - m_Pos->GetX());
    return (distanceToPlayer <= RADIUS);
}

void CEnemy::MoveTowardsPlayer() {
    if (TheCamera::Instance().GetTarget()->GetX() > m_Centre->GetX()) {
        m_RigidBody->ApplyForceX(MOVEMENT_SPEED * RIGHT);
        m_Rotation = Rotation::LEFT;
    } else if (TheCamera::Instance().GetTarget()->GetX() < m_Centre->GetX()) {
        m_RigidBody->ApplyForceX(MOVEMENT_SPEED * LEFT);
        m_Rotation = Rotation::RIGHT;
    }
}

void CEnemy::PerformAttack() {
    if (m_AttackTimer <= 0.0F) {
        TheCollisionHandler::Instance().EnemyAttack(ATTACK_DMG, ATTACK_RANGE, m_Rotation, m_Collider);
        m_AttackTimer = ATTACK_DELAY;
    } else {
        m_AttackTimer -= TheTimer::Instance().GetDeltaTime();
    }
}

void CEnemy::PerformJump() {
    m_JumpDelay = GenerateRandomNum();
    m_RigidBody->ApplyForceY(UP * JUMP_FORCE);
    m_IsJumping = true;
    m_JumpTimer = JUMP_TIME;
}

void CEnemy::ResetJump() {
    m_RigidBody->UnsetForce();
    m_IsJumping = false;
}

void CEnemy::EnemyCheckCollision() {
    UpdateHorizontalMovement();
    UpdateVerticalMovement();
}

void CEnemy::UpdateHorizontalMovement() {
    m_RigidBody->Update();
    m_LastSafePos->SetX(m_Pos->GetX());
    m_Pos->SetX(m_Pos->GetX() + m_RigidBody->GetPosition()->GetX());
    UpdateCollider();
    HandleHorizontalCollisions();
}

void CEnemy::UpdateVerticalMovement() {
    m_RigidBody->Update();
    m_LastSafePos->SetY(m_Pos->GetY());
    m_Pos->SetY(m_Pos->GetY() + m_RigidBody->GetPosition()->GetY());
    UpdateCollider();
    HandleVerticalCollisions();
}

void CEnemy::HandleHorizontalCollisions() {
    if (m_Collider.GetCollider().x < 0 ||
        m_Collider.GetCollider().x + m_Collider.GetCollider().w > TheGame::Instance().GetMapWidth() ||
        CCollisionHandler::Instance().MapCollision(m_Collider.GetCollider(), m_CurrHP) ||
        CCollisionHandler::Instance().CheckCollisionWithPlayer(m_Collider)) {
        m_Pos->SetX(m_LastSafePos->GetX());
    }
}

void CEnemy::HandleVerticalCollisions() {
    if (CCollisionHandler::Instance().MapCollision(m_Collider.GetCollider(), m_CurrHP) ||
        CCollisionHandler::Instance().CheckCollisionWithPlayer(m_Collider)) {
        m_IsGrounded = true;
        m_Pos->SetY(m_LastSafePos->GetY());
    } else {
        m_IsGrounded = false;
    }
}

json CEnemy::Save() const {
    //TODO
}

void CEnemy::Load(const json &jsonData) {
    //TODO
}

CEnemy::~CEnemy() = default;
