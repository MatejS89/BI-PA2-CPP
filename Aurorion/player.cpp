#include "player.h"

Player::Player(const char *texture, SDL_Renderer *renderer, int x, int y) : GameObject(texture, renderer, x, y) {}

GameObject *Player::clone() {
    return new Player(*this);
}

void Player::move(int dir) {
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

void Player::moveUp() {
    GameObject::m_yPos -= 6;
}

void Player::moveDown() {
    GameObject::m_yPos += 6;
}

void Player::moveLeft() {
    GameObject::m_xPos -= 6;
}

void Player::moveRight() {
    GameObject::m_xPos += 6;
}