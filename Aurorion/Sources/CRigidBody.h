#pragma once

#include "CVector2D.h"

#define LEFT -1
#define RIGHT 1
#define UP -1
#define DOWN 1

class CRigidBody {
public:
    CRigidBody();

    virtual ~CRigidBody();

    void SetMass(float mass);

    void SetGravity(float gravity);

    float GetGravity() const;

    float GetMass() const;

    void ApplyForce(const CVector2D &force);

    void ApplyForceX(const float force);

    void ApplyForceY(const float force);

    void UnsetForce();

    void ApplyFriction(const CVector2D &friction);

    void UnsetFriction();

    void Update(float dt);

    CVector2D &GetPosition();

    CVector2D &GetVelocity();

    CVector2D &GetAcceleration();

private:
    float m_Mass;
    float m_Gravity;
    CVector2D m_Force;
    CVector2D m_Friction;
    CVector2D m_Position;
    CVector2D m_Velocity;
    CVector2D m_Acceleration;
};
