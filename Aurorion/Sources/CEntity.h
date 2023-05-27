#pragma once

#include "CGameObject.h"
#include "SParamLoader.h"
#include "CVector2D.h"
#include "CRigidBody.h"
#include "CCollider.h"

class CEntity : public CGameObject {
public:
    CEntity(std::shared_ptr<SParamLoader> params);

    virtual void Draw();

    virtual bool Update();

    virtual void clean();

    std::shared_ptr<CVector2D> GetPosition();

    int GetCurrHp() const;

    int GetMaxHp() const;

    const SDL_Rect &GetCollider() const override;

protected:
    int m_W;
    int m_H;

    int m_currentRow;
    int m_currentFrame;

    std::string m_texture;

    std::shared_ptr<CRigidBody> m_RigidBody;

    std::shared_ptr<CVector2D> m_Pos;

    std::shared_ptr<CVector2D> m_LastSafePos;

    bool m_IsJumping;

    bool m_IsGrounded;

    float m_JumpTime;

    int m_CurrHP;

    int m_MaxHP;

    CCollider m_Collider;

    SDL_RendererFlip m_Flip;

    bool m_IsAlive;

    const int LEFT = -1;
    const int RIGHT = 1;
    const int UP = -1;
    const int DOWN = 1;
};