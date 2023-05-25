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

    virtual void Update(float deltaTime);

    virtual void clean();

    std::shared_ptr<CVector2D> GetPosition();

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

    CCollider m_Collider;

    SDL_RendererFlip m_Flip;
};