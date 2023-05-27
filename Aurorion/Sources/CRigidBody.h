#pragma once

#include "CVector2D.h"
#include <memory>
#include "CTimer.h"

class CRigidBody {
public:
    CRigidBody();

    virtual ~CRigidBody();

    void SetMass(float mass);

    void SetGravity(float gravity);

    float GetGravity() const;

    float GetMass() const;

    void ApplyForce(const CVector2D &force);

    void ApplyForceX(int force);

    void ApplyForceY(int force);

    void UnsetForce();

    void ApplyFriction(const CVector2D &friction);

    void UnsetFriction();

    void Update();

    void SetPosition(const CVector2D &pos);

    void SetVelocity(const CVector2D &vel);

    std::shared_ptr<CVector2D> GetPosition();

    CVector2D &GetVelocity();

    CVector2D &GetAcceleration();

private:
    float m_Mass;
    float m_Gravity;
    CVector2D m_Force;
    CVector2D m_Friction;
    std::shared_ptr<CVector2D> m_Position;
    CVector2D m_Velocity;
    CVector2D m_Acceleration;
};
