#include "CPlayer.h"
#include "CInputHandler.h"

CPlayer::CPlayer(std::shared_ptr<SParamLoader> params) : CEntity(params) {}

void CPlayer::draw() {
    CEntity::draw();
}

void CPlayer::update() {
    m_currentFrame = (((SDL_GetTicks() / 100) % 8));
    CEntity::m_RigitBody->ApplyForceX(
            CEntity::m_RigitBody->GetPosition().GetX() + CEntity::m_RigitBody->GetPosition().GetX());
    CEntity::m_RigitBody->ApplyForceY(
            CEntity::m_RigitBody->GetPosition().GetY() + CEntity::m_RigitBody->GetPosition().GetY());
    HandleInput();
    CEntity::update(CEntity::m_RigitBody);
}

void CPlayer::clean() {
}

void CPlayer::HandleInput() {
    TheInputHandler::Instance().Listen();
    CEntity::m_RigitBody->UnsetForce();
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP))
        CEntity::m_RigitBody->ApplyForceY(5 * UP);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_DOWN))
        CEntity::m_RigitBody->ApplyForceY(5 * DOWN);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_RIGHT))
        CEntity::m_RigitBody->ApplyForceX(5 * RIGHT);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT))
        CEntity::m_RigitBody->ApplyForceX(5 * LEFT);
}