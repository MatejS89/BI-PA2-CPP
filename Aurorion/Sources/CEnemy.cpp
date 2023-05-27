#include "CEnemy.h"
#include "CTimer.h"

CEnemy::CEnemy(std::shared_ptr<SParamLoader> params) : CEntity(params), m_JumpDelay(0.0F) {
    TheTextureManager::Instance().Load
            ("assets/Mob/Boar/Idle/Idle-Sheet.png", "BoarIdle");
    m_MaxHP = MAX_HP;
    m_CurrHP = MAX_HP;
}

void CEnemy::Draw() {
    CEntity::Draw();
}

bool CEnemy::Update(float deltaTime) {
    m_currentFrame = (((SDL_GetTicks() / 100) % 4));
//    std::cout << deltaTime << "     " << TheTimer::Instance().GetDeltaTime() << std::endl;
//    std::cout << TheCamera::Instance().GetTarget()->GetX() << " " << TheCamera::Instance().GetTarget()->GetY()
//              << std::endl;

    if (m_JumpDelay <= 0 && m_IsGrounded) {
        m_JumpDelay = GenerateRandomNum();
        m_RigidBody->ApplyForceY(UP * JUMP_FORCE);
        m_IsJumping = true;
        m_JumpTimer = JUMP_TIME;
    } else if (m_IsGrounded) {
        m_JumpDelay -= deltaTime;
    }
    m_JumpTimer -= deltaTime;
    if (m_JumpTimer <= 0.0F)
        m_RigidBody->UnsetForce();

    if (abs(TheCamera::Instance().GetTarget()->GetX() - m_Pos->GetX()) <= RADIUS) {
        if (TheCamera::Instance().GetTarget()->GetX() >= m_Pos->GetX() + m_W / 2)
            m_RigidBody->ApplyForceX(MOVEMENT_SPEED * RIGHT);
        if (TheCamera::Instance().GetTarget()->GetX() <= m_Pos->GetX() + m_W / 2)
            m_RigidBody->ApplyForceX(MOVEMENT_SPEED * LEFT);
    } else {
        m_RigidBody->UnsetForce();
    }
    return CEntity::Update(deltaTime);
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
