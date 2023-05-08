#include "player.h"

CPlayer::CPlayer(const char *texture, SDL_Renderer *renderer, int x, int y) : CGameObject(texture, renderer, x, y) {}

CGameObject *CPlayer::clone() {
    return new CPlayer(*this);
}

void CPlayer::move(int dir) {
    switch (dir) {
        case 0:
            moveUp();
            break;
        case 1:
            moveRight();
            break;
        case 2:
            moveDown();
            break;
        case 3:
            moveLeft();
            break;
    }
}

void CPlayer::moveUp() {
    CGameObject::m_yPos -= 6;
}

void CPlayer::moveDown() {
    CGameObject::m_yPos += 6;
}

void CPlayer::moveLeft() {
    CGameObject::m_xPos -= 6;
}

void CPlayer::moveRight() {
    CGameObject::m_xPos += 6;
}