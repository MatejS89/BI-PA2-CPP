#include "CEnemy.h"
#include "CTimer.h"

CEnemy::CEnemy(std::shared_ptr<SParamLoader> params) : CEntity(params) {
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
    if (abs(TheCamera::Instance().GetTarget()->GetX() - m_Pos->GetX()) <= RADIUS) {
        if (TheCamera::Instance().GetTarget()->GetX() >= m_Pos->GetX() + m_W / 2)
            m_RigidBody->ApplyForceX(MOVEMENT_SPEED * RIGHT);
        if (TheCamera::Instance().GetTarget()->GetX() <= m_Pos->GetX() + m_W / 2)
            m_RigidBody->ApplyForceX(MOVEMENT_SPEED * LEFT);
    } else {
        m_RigidBody->UnsetForce();
    }
//    std::cout << "V RANGEY" << std::endl;
    return CEntity::Update(deltaTime);
}

void CEnemy::clean() {
    CEntity::clean();
}
