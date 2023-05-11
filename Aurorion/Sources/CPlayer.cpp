#include "CPlayer.h"

CPlayer::CPlayer(const SParamLoader *params) : CEntity(params) {}

void CPlayer::draw() {
    CEntity::draw();
}

void CPlayer::update() {
    m_X -= 1;
    m_currentFrame = (((SDL_GetTicks() / 100) % 8));
}

void CPlayer::clean() {
}