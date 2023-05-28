#include "CEnemy.h"
#include "CTimer.h"

CEnemy::CEnemy(std::shared_ptr<SParamLoader> params) : CEntity(params), m_JumpDelay(0.0F), m_AttackTimer(0.0F) {
    TheTextureManager::Instance().Load
            ("assets/Mob/Boar/Idle/Idle-Sheet.png", "BoarIdle");
    m_MaxHP = MAX_HP;
    m_CurrHP = MAX_HP;
}

void CEnemy::Draw() {
    CEntity::Draw();
}

bool CEnemy::Update() {
    if (m_CurrHP <= 0)
        return false;
    m_currentFrame = (((SDL_GetTicks() / 100) % 4));
//    std::cout << deltaTime << "     " << TheTimer::Instance().GetDeltaTime() << std::endl;
//    std::cout << TheCamera::Instance().GetTarget()->GetX() << " " << TheCamera::Instance().GetTarget()->GetY()
//              << std::endl;

    RandomJump();
    FollowPlayer();
    CheckCollisionWithPlayer(m_Collider);
    return true;
}

void CEnemy::clean() {
    CEntity::clean();
}

float CEnemy::GenerateRandomNum() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(100.0F, 200.0F);
    return distribution(gen);
}

void CEnemy::RandomJump() {
    if (m_JumpDelay <= 0 && m_IsGrounded) {
        m_JumpDelay = GenerateRandomNum();
        m_RigidBody->ApplyForceY(UP * JUMP_FORCE);
        m_IsJumping = true;
        m_JumpTimer = JUMP_TIME;
    } else if (m_IsGrounded) {
        m_JumpDelay -= TheTimer::Instance().GetDeltaTime();
    }
    if (m_IsJumping && m_JumpTimer > 0.0F) {
        m_JumpTimer -= TheTimer::Instance().GetDeltaTime();
    } else if (m_JumpTimer <= 0.0F) {
        m_RigidBody->UnsetForce();
    }
}

void CEnemy::FollowPlayer() {
    if (abs(TheCamera::Instance().GetTarget()->GetX() - m_Pos->GetX()) <= RADIUS) {
        if (TheCamera::Instance().GetTarget()->GetX() > m_Pos->GetX() + m_W / 2) {
            m_RigidBody->ApplyForceX(MOVEMENT_SPEED * RIGHT);
            m_Rotation = Rotation::LEFT;
        }
        if (TheCamera::Instance().GetTarget()->GetX() < m_Pos->GetX() + m_W / 2) {
            m_RigidBody->ApplyForceX(MOVEMENT_SPEED * LEFT);
            m_Rotation = Rotation::RIGHT;
        }
        if (m_AttackTimer <= 0.0F) {
            TheCollisionHandler::Instance().EnemyAttack(ATTACK_DMG, ATTACK_RANGE, m_Rotation, m_Collider);
            m_AttackTimer = ATTACKDELAY;
        } else
            m_AttackTimer -= TheTimer::Instance().GetDeltaTime();
    } else {
        m_RigidBody->UnsetForce();
    }
}

void CEnemy::CheckCollisionWithPlayer(const CCollider &collider) {
    m_RigidBody->Update();
    m_LastSafePos->SetX(m_Pos->GetX());
    m_Pos->SetX(m_Pos->GetX() + m_RigidBody->GetPosition()->GetX());
    m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W,
                   m_H);
    if (m_Collider.GetCollider().x < 0)
        m_Pos->SetX(m_LastSafePos->GetX());
    if (m_Collider.GetCollider().x + m_Collider.GetCollider().w > TheGame::Instance().GetMapWidth()) {
        m_Pos->SetX(m_LastSafePos->GetX());
    }
    if (CCollisionHandler::Instance().MapCollision(m_Collider.GetCollider(), m_CurrHP) ||
        CCollisionHandler::Instance().EnemyCheckCollision(m_Collider)) {
        m_Pos->SetX(m_LastSafePos->GetX());
    }
    m_RigidBody->Update();
    m_LastSafePos->SetY(m_Pos->GetY());
    m_Pos->SetY(m_Pos->GetY() + m_RigidBody->GetPosition()->GetY());
    m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W,
                   m_H);
    if (CCollisionHandler::Instance().MapCollision(m_Collider.GetCollider(), m_CurrHP) ||
        CCollisionHandler::Instance().EnemyCheckCollision(m_Collider)) {
        m_IsGrounded = true;
        m_Pos->SetY(m_LastSafePos->GetY());
    } else {
        m_IsGrounded = false;
    }
    *m_Centre = *m_Pos + CVector2D(m_W / 2, m_H / 2);
}
