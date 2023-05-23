#include "CEntity.h"
#include "CGame.h"

CEntity::CEntity(std::shared_ptr<SParamLoader> params) : CGameObject(params),
                                                         m_W(params->m_W),
                                                         m_H(params->m_H),
                                                         m_currentRow(1),
                                                         m_currentFrame(1),
                                                         m_texture(params->m_texture),
                                                         m_RigitBody(std::make_shared<CRigidBody>()) {
    m_RigitBody->SetPosition({params->m_X, params->m_Y});
}

void CEntity::draw() {
    CTextureManager::Instance().DrawFrame(m_texture, m_RigitBody->GetPosition().GetX(),
                                          m_RigitBody->GetPosition().GetY(), m_W, m_H, m_currentRow,
                                          m_currentFrame);
}

void CEntity::update(std::shared_ptr<CRigidBody> body) {
    m_RigitBody->Update(0.5);
}

void CEntity::clean() {
}