#include "CPlayer.h"
#include "CInputHandler.h"

CPlayer::CPlayer(std::shared_ptr<SParamLoader> params) : CEntity(params),
                                                         m_RigidBody(std::make_shared<CRigidBody>()) {}

void CPlayer::draw() {
    CEntity::draw();
}

void CPlayer::update() {
    m_currentFrame = (((SDL_GetTicks() / 100) % 8));
    m_velocity.SetX(m_velocity.GetX() + m_RigidBody->GetPosition().GetX());
    m_velocity.SetY(m_velocity.GetY() + m_RigidBody->GetPosition().GetY());
    HandleInput();
    m_RigidBody->Update(0.2);
    CEntity::update(m_RigidBody);
}

void CPlayer::clean() {
}

void CPlayer::HandleInput() {
    TheInputHandler::Instance().Listen();
    m_RigidBody->UnsetForce();
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP))
        m_RigidBody->ApplyForceY(5 * UP);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_DOWN))
        m_RigidBody->ApplyForceY(5 * DOWN);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_RIGHT))
        m_RigidBody->ApplyForceX(5 * RIGHT);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT))
        m_RigidBody->ApplyForceX(5 * LEFT);
}