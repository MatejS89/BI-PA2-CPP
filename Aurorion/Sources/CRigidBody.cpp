#include "CRigidBody.h"
#include <iostream>

#define CONST_MASS 1.0F
#define CONST_GRAVITY 4.0F


CRigidBody::CRigidBody() : m_Mass(CONST_MASS), m_Gravity(CONST_GRAVITY),
                           m_Position(std::make_shared<CVector2D>(0, 0)) {}

void CRigidBody::SetMass(float mass) {
    m_Mass = mass;
}

void CRigidBody::SetGravity(float gravity) {
    m_Gravity = gravity;
}

float CRigidBody::GetGravity() const {
    return m_Gravity;
}

float CRigidBody::GetMass() const {
    return m_Mass;
}

void CRigidBody::ApplyForce(const CVector2D &force) {
    m_Force = force;
}

void CRigidBody::UnsetForce() {
    m_Force = {0, 0};
}

void CRigidBody::ApplyFriction(const CVector2D &friction) {
    m_Friction = friction;
}

void CRigidBody::UnsetFriction() {
    m_Friction = {0, 0};
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

CVector2D &CRigidBody::GetAcceleration() {
    return m_Acceleration;
}

void CRigidBody::ApplyForceY(const int force) {
    m_Force.SetY(force);
}

void CRigidBody::ApplyForceX(const int force) {
    m_Force.SetX(force);
}

void CRigidBody::SetPosition(const CVector2D &pos) {
    m_Position->SetX(pos.GetX());
    m_Position->SetY(pos.GetY());
}

void CRigidBody::SetVelocity(const CVector2D &vel) {
    m_Velocity = {vel.GetX(), vel.GetY()};
}

CRigidBody::~CRigidBody() = default;
