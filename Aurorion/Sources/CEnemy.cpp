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
    CEntity::Update(deltaTime);
}

void CEnemy::clean() {
    CEntity::clean();
}
