#include "CRigidBody.h"

CRigidBody::CRigidBody() : m_Mass(CONST_MASS), m_Gravity(CONST_GRAVITY),
                           m_Friction(0, 0),
                           m_Position(std::make_shared<CVector2D>(0, 0)) {}

float CRigidBody::GetGravity() const {
    return m_Gravity;
}

void CRigidBody::UnsetForce() {
    m_Force = {0, 0};
}

void CRigidBody::Update() {
    m_Acceleration.SetX(m_Force.GetX() + m_Friction.GetX() / m_Mass);
    m_Acceleration.SetY(m_Gravity + m_Force.GetY() / m_Mass);
    m_Velocity = m_Acceleration * TheTimer::Instance().GetDeltaTime();
    *m_Position = m_Velocity * TheTimer::Instance().GetDeltaTime();
}

std::shared_ptr<CVector2D> CRigidBody::GetPosition() {
    return m_Position;
}

CVector2D &CRigidBody::GetVelocity() {
    return m_Velocity;
}

void CRigidBody::ApplyForceY(const int force) {
    m_Force.SetY(force);
}

void CRigidBody::ApplyForceX(const int force) {
    m_Force.SetX(force);
}

CRigidBody::~CRigidBody() = default;
