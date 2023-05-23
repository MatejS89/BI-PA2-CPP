#include "CPlayer.h"
#include "CInputHandler.h"

CPlayer::CPlayer(std::shared_ptr<SParamLoader> params) : CEntity(params) {}

void CPlayer::draw() {
    CEntity::draw();
}

void CPlayer::update(float deltaTime) {
    m_currentFrame = (((SDL_GetTicks() / 100) % 4));
    CEntity::m_RigidBody->ApplyForceX(
            CEntity::m_RigidBody->GetPosition().GetX() + CEntity::m_RigidBody->GetPosition().GetX());
    CEntity::m_RigidBody->ApplyForceY(
            CEntity::m_RigidBody->GetPosition().GetY() + CEntity::m_RigidBody->GetPosition().GetY());
    HandleInput();
    CEntity::update(deltaTime);
}

void CPlayer::clean() {
}

void CPlayer::HandleInput() {
    TheInputHandler::Instance().Listen();
    CEntity::m_RigidBody->UnsetForce();
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP))
        CEntity::m_RigidBody->ApplyForceY(1.5 * UP);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_DOWN))
        CEntity::m_RigidBody->ApplyForceY(1.5 * DOWN);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_RIGHT))
        CEntity::m_RigidBody->ApplyForceX(1.5 * RIGHT);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT))
        CEntity::m_RigidBody->ApplyForceX(1.5 * LEFT);
}