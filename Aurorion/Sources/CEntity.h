#pragma once

#include "CGameObject.h"
#include "SParamLoader.h"
#include "CVector2D.h"
#include "CRigidBody.h"
#include "CCollider.h"

enum class Rotation {
    RIGHT,
    LEFT
};

enum Direction {
    LEFT = -1,
    RIGHT = 1,
    UP = -1,
    DOWN = 1,
};

class CEntity : public CGameObject {
public:
    CEntity(std::shared_ptr<SParamLoader> params);

    ~CEntity() override;

    virtual void Draw();

    virtual bool Update();

    void ReduceHp(int dmg) override;

    std::shared_ptr<CVector2D> GetPosition();

    int GetCurrHp() const;

    int GetMaxHp() const;

    const SDL_Rect &GetCollider() const override;

    void IncreaseFallCounter();

    void DealFallDamage();

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

    Rotation m_Rotation;

    float m_FallTime;

    bool m_ImmuneToFall;
};