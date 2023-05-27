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
                                                         m_Pos(std::make_shared<CVector2D>(params->m_X,
                                                                                           params->m_Y)),
                                                         m_LastSafePos(std::make_shared<CVector2D>(
                                                                 params->m_X, params->m_Y)),
                                                         m_IsJumping(false),
                                                         m_IsGrounded(false),
                                                         m_Collider(
                                                                 params->m_X, params->m_Y, params->m_W,
                                                                 params->m_H),
                                                         m_Flip(SDL_FLIP_NONE),
                                                         m_IsAlive(true) {
    m_Centre = std::make_shared<CVector2D>(params->m_X + m_W / 2, params->m_Y + m_H / 2);
    m_RigidBody->SetPosition({params->m_X, params->m_Y});
}

void CEntity::Draw() {
    CTextureManager::Instance().DrawFrame(m_texture, m_Pos->GetX(),
                                          m_Pos->GetY(), m_W, m_H, m_currentRow,
                                          m_currentFrame, m_Flip);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 255, 0, 0, 255);
    const CVector2D &cam = TheCamera::Instance().GetPosition();
    SDL_Rect colli = m_Collider.GetCollider();
    colli.x -= (cam.GetX());
    colli.y -= (cam.GetY());
    std::cout << m_Collider.GetCollider().w << std::endl;
    SDL_RenderDrawRect(TheGame::Instance().GetRenderer(), &colli);
}

bool CEntity::Update() {
    if (m_CurrHP <= 0)
        return false;

    m_RigidBody->Update();
    m_LastSafePos->SetX(m_Pos->GetX());
    m_Pos->SetX(m_Pos->GetX() + m_RigidBody->GetPosition()->GetX());
    m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W,
                   m_H);
    if (m_Collider.GetCollider().x < 0)
        m_Pos->SetX(m_LastSafePos->GetX());
    if (m_Collider.GetCollider().x + m_Collider.GetCollider().w > TheGame::Instance().GetMapWidth()) {
//        std::cout << TheGame::Instance().GetMapWidth() << std::endl;
        m_Pos->SetX(m_LastSafePos->GetX());
    }
    if (CCollisionHandler::Instance().MapCollision(m_Collider.GetCollider()) ||
        CCollisionHandler::Instance().PlayerCheckCollison()) {
        m_Pos->SetX(m_LastSafePos->GetX());
    }
    m_RigidBody->Update();
    m_LastSafePos->SetY(m_Pos->GetY());
    m_Pos->SetY(m_Pos->GetY() + m_RigidBody->GetPosition()->GetY());
    m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W,
                   m_H);
    if (CCollisionHandler::Instance().MapCollision(m_Collider.GetCollider()) ||
        CCollisionHandler::Instance().PlayerCheckCollison()) {
        m_IsGrounded = true;
        m_Pos->SetY(m_LastSafePos->GetY());
    } else {
        m_IsGrounded = false;
    }
    *m_Centre = *m_Pos + CVector2D(m_W / 2, m_H / 2);

//    std::cout << m_CurrHP << std::endl;
    return true;
}

void CEntity::clean() {
}

std::shared_ptr<CVector2D> CEntity::GetPosition() {
    return m_RigidBody->GetPosition();
}

int CEntity::GetCurrHp() const {
    return m_CurrHP;
}

int CEntity::GetMaxHp() const {
    return m_MaxHP;
}

const SDL_Rect &CEntity::GetCollider() const {
    return m_Collider.GetCollider();
}

void CEntity::ReduceHp(int dmg) {
    m_CurrHP -= dmg;
}
