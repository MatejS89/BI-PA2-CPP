#include "CEnemy.h"

CEnemy::CEnemy(std::shared_ptr<SParamLoader> params) : CEntity(params) {
    TheTextureManager::Instance().Load
            ("assets/Mob/Boar/Idle/Idle-Sheet.png", "BoarIdle");
}

void CEnemy::Draw() {
    CEntity::Draw();
}

void CEnemy::Update(float deltaTime) {
    m_currentFrame = (((SDL_GetTicks() / 100) % 4));
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
    CEntity::Update(deltaTime);
}

void CEnemy::clean() {
    CEntity::clean();
}
