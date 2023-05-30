#include "CEntity.h"
#include "CGame.h"

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

CEntity::CEntity() : CGameObject(), m_RigidBody(std::make_shared<CRigidBody>()), m_Pos(std::make_shared<CVector2D>()),
                     m_LastSafePos(std::make_shared<CVector2D>()) {}

void CEntity::Load(const json &jsonData) {

}

CEntity::~CEntity() = default;
