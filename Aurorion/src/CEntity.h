#pragma once

#include "CGameObject.h"
#include "CVector2D.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "EDirection.h"
#include "ERotation.h"
#include "CCollisionHandler.h"

using json = nlohmann::json;

/**
 * @class CEntity
 * @brief The base class for game entities, derived from CGameObject.
 */
class CEntity : public CGameObject {
public:
    ~CEntity() override;

    /**
     * @brief Draws the entity to the screen with the given texture id stored in m_Texture.
     */
    virtual void Draw();

    /**
     * @brief Updates the game object.
     * @return True if the update m_CurrHP > 0, false otherwise.
     */
    virtual bool Update();

    void ReduceHp(int dmg) override;

    int GetCurrHp() const override;

    int GetMaxHp() const override;

    const SDL_Rect &GetCollider() const override;

    void IncreaseFallCounter();

    void DealFallDamage();

    /**
     * @brief Updates the collider based on current position.
     */
    void UpdateCollider();

    /**
     * @brief Used to save attributes of classes derived from CEntity.
     * @return A json element containing the save data.
     */
    virtual json Save() const = 0;

    /**
     * @brief Loads the entity from a JSON object.
     * @param jsonData The JSON data to load from.
     */
    virtual void Load(const json &jsonData);

protected:
    CEntity();

    void SaveEntityData(json &jsonData) const;

    int m_W;

    int m_H;

    int m_CurrentRow;

    int m_CurrentFrame;

    std::string m_Texture;

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