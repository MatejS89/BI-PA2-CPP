#include "CEntity.h"
#include "CGame.h"

CEntity::CEntity(std::shared_ptr<SParamLoader> params) : CGameObject(params),
                                                         m_pos(params->m_X,
                                                               params->m_Y),
                                                         m_velocity(0, 0),
                                                         m_W(params->m_W),
                                                         m_H(params->m_H),
                                                         m_currentRow(1),
                                                         m_currentFrame(1),
                                                         m_texture(params->m_texture) {}

void CEntity::draw() {
    CTextureManager::Instance().DrawFrame(m_texture, m_pos.GetX(), m_pos.GetY(), m_W, m_H, m_currentRow,
                                          m_currentFrame,
                                          TheGame::Instance().GetRenderer());
}

void CEntity::update() {
    m_pos += m_velocity;
}

void CEntity::clean() {
}