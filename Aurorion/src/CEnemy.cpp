#include "CEnemy.h"
#include "CTimer.h"

CEnemy::CEnemy() : CEntity() {
    // TODO add loading of source_texture to Load method
    TheTextureManager::Instance().Load
            ("assets/Mob/Boar/Idle/Idle-Sheet.png", "BoarIdle");
}

CEnemy::~CEnemy() = default;

std::shared_ptr<CGameObject> CEnemy::Create() {
    return std::make_shared<CEnemy>();
}

void CEnemy::Load(const json &jsonData) {
    m_Collider.SetBuffer(0, 0, 7, 2);
    CEntity::Load(jsonData);
    m_IsJumping = jsonData["IS_JUMPING"];
    m_IsGrounded = jsonData["IS_GROUNDED"];
    m_FallTime = jsonData["FALL_TIME"];
    m_ImmuneToFall = jsonData["IMMUNE_TO_FALL"];
    m_Rotation = jsonData["ROTATION"];
    JUMP_FORCE = jsonData["JUMP_FORCE"];
    JUMP_TIME = jsonData["JUMP_TIME"];
    MOVEMENT_SPEED = jsonData["MOVEMENT_SPEED"];
    RADIUS = jsonData["RADIUS"];
    ATTACK_DMG = jsonData["ATTACK_DMG"];
    ATTACK_RANGE = jsonData["ATTACK_RANGE"];
    ATTACK_DELAY = jsonData["ATTACK_DELAY"];
    m_AttackTimer = jsonData["ATTACK_TIMER"];
    m_JumpDelay = jsonData["JUMP_DELAY"];
    m_JumpTimer = jsonData["JUMP_TIMER"];
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

json CEnemy::Save() const {
    json jsonData;
    SaveEntityData(jsonData);
    jsonData["JUMP_FORCE"] = JUMP_FORCE;
    jsonData["JUMP_TIME"] = JUMP_TIME;
    jsonData["MOVEMENT_SPEED"] = MOVEMENT_SPEED;
    jsonData["ATTACK_DMG"] = ATTACK_DMG;
    jsonData["ATTACK_RANGE"] = ATTACK_RANGE;
    jsonData["ATTACK_DELAY"] = ATTACK_DELAY;
    jsonData["ATTACK_TIMER"] = m_AttackTimer;
    jsonData["JUMP_DELAY"] = m_JumpDelay;
    jsonData["RADIUS"] = RADIUS;
    jsonData["JUMP_TIMER"] = m_JumpTimer;
    return jsonData;
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

bool CEnemy::IsPlayerInRange() const {
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

float CEnemy::GenerateRandomNum() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(100.0F, 200.0F);
    return distribution(gen);
}
