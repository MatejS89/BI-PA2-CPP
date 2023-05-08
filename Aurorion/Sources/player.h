#pragma once

#include "CGameObject.h"

class CPlayer : public CGameObject {
public:
    CPlayer(const char *texture, SDL_Renderer *renderer, int x, int y);

    CGameObject *clone() override;

    void move(int dir) override;

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();
};