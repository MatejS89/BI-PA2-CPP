#include "CEntity.h"
#include "CGame.h"

CEntity::CEntity(const SParamLoader *params) : CGameObject(params),
                                               m_X(params->m_X),
                                               m_Y(params->m_Y),
                                               m_W(params->m_W),
                                               m_H(params->m_H),
                                               m_currentRow(1),
                                               m_currentFrame(1),
                                               m_texture(params->m_texture) {}

void CEntity::draw() {
    CTextureManager::Instance()->DrawFrame(m_texture, m_X, m_Y, m_W, m_H, m_currentRow, m_currentFrame,
                                           TheGame::Instance()->GetRenderer());
}

void CEntity::update() {

}

void CEntity::clean() {
    
}