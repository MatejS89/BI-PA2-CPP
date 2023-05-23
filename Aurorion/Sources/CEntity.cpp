#include "CEntity.h"
#include "CGame.h"

CEntity::CEntity(std::shared_ptr<SParamLoader> params) : CGameObject(params),
                                                         m_W(params->m_W),
                                                         m_H(params->m_H),
                                                         m_currentRow(1),
                                                         m_currentFrame(1),
                                                         m_texture(params->m_texture),
                                                         m_RigidBody(std::make_shared<CRigidBody>()) {
    m_RigidBody->SetPosition({params->m_X, params->m_Y});
}

void CEntity::draw() {
    CTextureManager::Instance().DrawFrame(m_texture, m_RigidBody->GetPosition().GetX(),
                                          m_RigidBody->GetPosition().GetY(), m_W, m_H, m_currentRow,
                                          m_currentFrame);
}

void CEntity::update(std::shared_ptr<CRigidBody> body) {
    m_RigidBody->Update(0.5);
}

void CEntity::clean() {
}