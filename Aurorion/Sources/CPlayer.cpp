#include "CPlayer.h"
#include "CInputHandler.h"

CPlayer::CPlayer(std::shared_ptr<SParamLoader> params) : CEntity(params) {}

void CPlayer::draw() {
    CEntity::draw();
}

void CPlayer::update() {
    m_currentFrame = (((SDL_GetTicks() / 100) % 8));
    HandleInput();
    CEntity::update();
}

void CPlayer::clean() {
}

void CPlayer::HandleInput() {
    TheInputHandler::Instance().Listen();

    m_velocity.SetY(0);
    m_velocity.SetX(0);

    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_UP))
        m_velocity.SetY(-2);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_DOWN))
        m_velocity.SetY(2);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_RIGHT))
        m_velocity.SetX(2);
    if (TheInputHandler::Instance().IsKeyDown(SDL_SCANCODE_LEFT))
        m_velocity.SetX(-2);
}