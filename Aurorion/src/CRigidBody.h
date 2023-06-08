#pragma once

#include "CVector2D.h"
#include <memory>
#include "CTimer.h"

/**
 * @class CRigidBody
 * @brief Represents the rigid body and physics of a game object.
 */
class CRigidBody {
public:
    CRigidBody();

    virtual ~CRigidBody();

    float GetGravity() const;

    void ApplyForceX(int force);

    void ApplyForceY(int force);

    void UnsetForce();

    /**
     * @brief Updates the current position of the rigid body based on on the acceleration, velocity, gravity, friction
     * and mass.
     */
    void Update();

    std::shared_ptr<CVector2D> GetPosition();

    CVector2D &GetVelocity();

private:
    const float CONST_MASS = 1.0F;

    const float CONST_GRAVITY = 4.0F;

    float m_Mass;

    float m_Gravity;

    CVector2D m_Force;

    CVector2D m_Friction;

    std::shared_ptr<CVector2D> m_Position;

    CVector2D m_Velocity;

    CVector2D m_Acceleration;
};
