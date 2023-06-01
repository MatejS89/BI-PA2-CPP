#pragma once

#include "CGameObject.h"
#include "SParamLoader.h"
#include "CVector2D.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "json.hpp"
#include "EDirection.h"
#include "ERotation.h"

using json = nlohmann::json;

/**
 * @class CEntity
 * @brief The base class for game entities, derived from CGameObject.
 */
class CEntity : public CGameObject {
public:
    CEntity();

    ~CEntity() override;

    virtual void Draw();

    virtual bool Update();

    void ReduceHp(int dmg) override;

    int GetCurrHp() const override;

    int GetMaxHp() const override;

    const SDL_Rect &GetCollider() const override;

    void IncreaseFallCounter();

    void DealFallDamage();

    void UpdateCollider();

    virtual json Save() const = 0;

    virtual void Load(const json &jsonData);

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