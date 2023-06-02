#include "CEnemy.h"
#include "CTimer.h"

CEnemy::CEnemy() : CEntity() {
    TheTextureManager::Instance().Load
            ("assets/Mob/Boar/Idle/Idle-Sheet.png", "BoarIdle");
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
    json jsonData;
    jsonData["WIDTH"] = m_W;
    jsonData["HEIGHT"] = m_H;
    jsonData["CURRENT_ROW"] = m_currentRow;
    jsonData["CURRENT_FRAME"] = m_currentFrame;
    jsonData["TEXTURE"] = m_texture;
    jsonData["POS_X"] = m_Pos->GetX();
    jsonData["POS_Y"] = m_Pos->GetY();
    jsonData["LAST_SAFE_POSX"] = m_LastSafePos->GetX();
    jsonData["LAST_SAFE_POSY"] = m_LastSafePos->GetY();
    m_RigidBody->SetPosition(*m_Pos);
    jsonData["IS_JUMPING"] = m_IsJumping;
    jsonData["IS_GROUNDED"] = m_IsGrounded;
    jsonData["FALL_TIME"] = m_FallTime;
    jsonData["IMMUNE_TO_FALL"] = m_ImmuneToFall;
    jsonData["ROTATION"] = m_Rotation;
    jsonData["JUMP_FORCE"] = JUMP_FORCE;
    jsonData["JUMP_TIME"] = JUMP_TIME;
    jsonData["MOVEMENT_SPEED"] = MOVEMENT_SPEED;
    jsonData["CURR_HP"] = m_CurrHP;
    jsonData["MAX_HP"] = m_MaxHP;
    jsonData["ATTACK_DMG"] = ATTACK_DMG;
    jsonData["ATTACK_RANGE"] = ATTACK_RANGE;
    jsonData["ATTACK_DELAY"] = ATTACK_DELAY;
    jsonData["ATTACK_TIMER"] = m_AttackTimer;
    jsonData["JUMP_DELAY"] = m_JumpDelay;
    jsonData["RADIUS"] = RADIUS;
    jsonData["JUMP_TIMER"] = m_JumpTimer;
    m_Centre->SetX(m_Pos->GetX() + m_W / 2);
    m_Centre->SetY(m_Pos->GetY() + m_H / 2);
    return jsonData;
}

void CEnemy::Load(const json &jsonData) {
    m_W = jsonData["WIDTH"];
    m_H = jsonData["HEIGHT"];
    m_currentRow = jsonData["CURRENT_ROW"];
    m_currentFrame = jsonData["CURRENT_FRAME"];
    m_texture = jsonData["TEXTURE"];
    m_Pos->SetX(jsonData["POS_X"]);
    m_Pos->SetY(jsonData["POS_Y"]);
    m_LastSafePos->SetX(jsonData["LAST_SAFE_POSX"]);
    m_LastSafePos->SetY(jsonData["LAST_SAFE_POSY"]);
    m_IsJumping = jsonData["IS_JUMPING"];
    m_IsGrounded = jsonData["IS_GROUNDED"];
    m_FallTime = jsonData["FALL_TIME"];
    m_ImmuneToFall = jsonData["IMMUNE_TO_FALL"];
    m_Rotation = jsonData["ROTATION"];
    JUMP_FORCE = jsonData["JUMP_FORCE"];
    JUMP_TIME = jsonData["JUMP_TIME"];
    MOVEMENT_SPEED = jsonData["MOVEMENT_SPEED"];
    m_CurrHP = jsonData["CURR_HP"];
    m_MaxHP = jsonData["MAX_HP"];
    RADIUS = jsonData["RADIUS"];
    ATTACK_DMG = jsonData["ATTACK_DMG"];
    ATTACK_RANGE = jsonData["ATTACK_RANGE"];
    ATTACK_DELAY = jsonData["ATTACK_DELAY"];
    m_AttackTimer = jsonData["ATTACK_TIMER"];
    m_JumpDelay = jsonData["JUMP_DELAY"];
    m_JumpTimer = jsonData["JUMP_TIMER"];
    m_Collider.SetBuffer(0, 0, 7, 2);
    m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W, m_H);
    while (TheCollisionHandler::Instance().MapCollision(m_Collider.GetCollider(), m_CurrHP)) {
        m_Pos->SetY(m_Pos->GetY() + 10);
        m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W, m_H);
    }
    m_CurrHP = jsonData["CURR_HP"];
}

std::shared_ptr<CGameObject> CEnemy::Create() {
    return std::make_shared<CEnemy>();
}

CEnemy::~CEnemy() = default;
