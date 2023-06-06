#include "CEntity.h"
#include "CGame.h"

CEntity::CEntity() : CGameObject(), m_RigidBody(std::make_shared<CRigidBody>()), m_Pos(std::make_shared<CVector2D>()),
                     m_LastSafePos(std::make_shared<CVector2D>()) {}

CEntity::~CEntity() = default;

void CEntity::Draw() {
    CTextureManager::Instance().DrawFrame(m_texture, m_Pos->GetX(),
                                          m_Pos->GetY(), m_W, m_H, m_currentRow,
                                          m_currentFrame,
                                          m_Rotation == Rotation::RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
//    SDL_Color tmp;
//    SDL_GetRenderDrawColor(TheGame::Instance().GetRenderer(), &tmp.r, &tmp.g, &tmp.b, &tmp.a);
//    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 255, 0, 0, 255);
//    const CVector2D &cam = TheCamera::Instance().GetPosition();
//    SDL_Rect colli = m_Collider.GetCollider();
//    colli.x -= (cam.GetX());
//    colli.y -= (cam.GetY());
//    SDL_RenderDrawRect(TheGame::Instance().GetRenderer(), &colli);
//    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), tmp.r, tmp.g, tmp.b, tmp.a);
}

bool CEntity::Update() {
    if (m_CurrHP <= 0)
        return false;
    *m_Centre = *m_Pos + CVector2D(m_W / 2, m_H / 2);
    return true;
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

void CEntity::Load(const json &jsonData) {
    m_W = jsonData["WIDTH"];
    m_H = jsonData["HEIGHT"];
    m_currentRow = jsonData["CURRENT_ROW"];
    m_currentFrame = jsonData["CURRENT_FRAME"];
    m_texture = jsonData["TEXTURE"];
    m_Pos->SetX(jsonData["POS_X"]);
    m_Pos->SetY(jsonData["POS_Y"]);
    m_LastSafePos->SetX(jsonData["LAST_SAFE_POSX"]);
    m_LastSafePos->SetY(jsonData["LAST_SAFE_POSY"]);
    m_ImmuneToFall = jsonData["IMMUNE_TO_FALL"];
    m_Rotation = jsonData["ROTATION"];
    m_CurrHP = jsonData["CURR_HP"];
    m_MaxHP = jsonData["MAX_HP"];
    m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W, m_H);
    while (TheCollisionHandler::Instance().MapCollision(m_Collider.GetCollider(), m_CurrHP)) {
        m_Pos->SetY(m_Pos->GetY() - 10);
        m_Collider.Set(m_Pos->GetX(), m_Pos->GetY(), m_W, m_H);
    }
    m_CurrHP = jsonData["CURR_HP"];
}

void CEntity::SaveEntityData(json &jsonData) const {
    jsonData["WIDTH"] = m_W;
    jsonData["HEIGHT"] = m_H;
    jsonData["CURRENT_ROW"] = m_currentRow;
    jsonData["CURRENT_FRAME"] = m_currentFrame;
    jsonData["TEXTURE"] = m_texture;
    jsonData["POS_X"] = m_Pos->GetX();
    jsonData["POS_Y"] = m_Pos->GetY();
    jsonData["LAST_SAFE_POSX"] = m_LastSafePos->GetX();
    jsonData["LAST_SAFE_POSY"] = m_LastSafePos->GetY();
    jsonData["IS_JUMPING"] = m_IsJumping;
    jsonData["IS_GROUNDED"] = m_IsGrounded;
    jsonData["FALL_TIME"] = m_FallTime;
    jsonData["IMMUNE_TO_FALL"] = m_ImmuneToFall;
    jsonData["ROTATION"] = m_Rotation;
    jsonData["CURR_HP"] = m_CurrHP;
    jsonData["MAX_HP"] = m_MaxHP;
}
