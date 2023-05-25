#include "CEntity.h"
#include "CGame.h"
#include "CCollisionHandler.h"

CEntity::CEntity(std::shared_ptr<SParamLoader> params) : CGameObject(params),
                                                         m_W(params->m_W),
                                                         m_H(params->m_H),
                                                         m_currentRow(1),
                                                         m_currentFrame(1),
                                                         m_texture(params->m_texture),
                                                         m_RigidBody(std::make_shared<CRigidBody>()),
                                                         m_Collider({static_cast<int>(params->m_X),
                                                                     static_cast<int>(params->m_Y), params->m_W,
                                                                     params->m_H}),
                                                         m_Pos(std::make_shared<CVector2D>(params->m_X, params->m_Y)),
                                                         m_LastSafePos(std::make_shared<CVector2D>(
                                                                 params->m_X, params->m_Y)) {
    m_Centre = std::make_shared<CVector2D>(params->m_X + m_W / 2, params->m_Y + m_H / 2);
    m_RigidBody->SetPosition({params->m_X, params->m_Y});
}

void CEntity::draw() {
    CTextureManager::Instance().DrawFrame(m_texture, m_Pos->GetX(),
                                          m_Pos->GetY(), m_W, m_H, m_currentRow,
                                          m_currentFrame);
    const CVector2D &cam = TheCamera::Instance().GetPosition();
    SDL_Rect colli = m_Collider;
    colli.x -= cam.GetX();
    colli.y -= cam.GetY();
//    std::cout << colli.x << " " << colli.y << std::endl;
    SDL_RenderDrawRect(TheGame::Instance().GetRenderer(), &colli);
}

void CEntity::update(float deltaTime) {
    m_RigidBody->Update(deltaTime);
    m_LastSafePos->SetX(m_Pos->GetX());
    m_Pos->SetX(m_Pos->GetX() + m_RigidBody->GetPosition()->GetX());
    *m_Centre = *m_Pos + CVector2D(m_W / 2, m_H / 2);
    m_Collider = {static_cast<int>(m_Pos->GetX()),
                  static_cast<int>(m_Pos->GetY()), m_Collider.w, m_Collider.h};
    if (CCollisionHandler::Instance().MapCollision(m_Collider)) {
        m_Pos->SetX(m_LastSafePos->GetX());
    }
    m_RigidBody->Update(deltaTime);
    m_LastSafePos->SetY(m_Pos->GetY());
    m_Pos->SetY(m_Pos->GetY() + m_RigidBody->GetPosition()->GetY());
    *m_Centre = *m_Pos + CVector2D(m_W / 2, m_H / 2);
    m_Collider = {static_cast<int>(m_Pos->GetX()),
                  static_cast<int>(m_Pos->GetY()), m_Collider.w, m_Collider.h};
    if (CCollisionHandler::Instance().MapCollision(m_Collider)) {
        m_Pos->SetY(m_LastSafePos->GetY());
    }
}

void CEntity::clean() {
}

std::shared_ptr<CVector2D> CEntity::GetPosition() {
    return m_RigidBody->GetPosition();
}
