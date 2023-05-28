#include "CEntity.h"
#include "CGame.h"

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
                                                         m_Rotation(Rotation::RIGHT),
                                                         m_FallTime(0.0F),
                                                         m_ImmuneToFall(true) {
    m_Centre = std::make_shared<CVector2D>(params->m_X + m_W / 2, params->m_Y + m_H / 2);
    m_RigidBody->SetPosition({params->m_X, params->m_Y});
}

void CEntity::Draw() {
    CTextureManager::Instance().DrawFrame(m_texture, m_Pos->GetX(),
                                          m_Pos->GetY(), m_W, m_H, m_currentRow,
                                          m_currentFrame,
                                          m_Rotation == Rotation::RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    SDL_Color tmp;
    SDL_GetRenderDrawColor(TheGame::Instance().GetRenderer(), &tmp.r, &tmp.g, &tmp.b, &tmp.a);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 255, 0, 0, 255);
    const CVector2D &cam = TheCamera::Instance().GetPosition();
    SDL_Rect colli = m_Collider.GetCollider();
    colli.x -= (cam.GetX());
    colli.y -= (cam.GetY());
    SDL_RenderDrawRect(TheGame::Instance().GetRenderer(), &colli);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), tmp.r, tmp.g, tmp.b, tmp.a);
}

bool CEntity::Update() {
    if (m_CurrHP <= 0)
        return false;
    *m_Centre = *m_Pos + CVector2D(m_W / 2, m_H / 2);
    return true;
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

void CEntity::IncreaseFallCounter() {
    if (m_RigidBody->GetVelocity().GetY() > 0 && !m_IsGrounded)
        m_FallTime += TheTimer::Instance().GetDeltaTime();
}

void CEntity::DealFallDamage() {
    if (m_FallTime >= 70.0F && !m_ImmuneToFall) {
        m_CurrHP -= m_FallTime * m_RigidBody->GetGravity() * 0.01F;
    }
}

void CEntity::UpdateCollider() {
    m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W, m_H);
}

CEntity::~CEntity() = default;
