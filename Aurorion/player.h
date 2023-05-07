#pragma once

#include "GameObject.h"

class Player : public GameObject {
public:
    Player(const char *texture, SDL_Renderer *renderer, int x, int y);

    GameObject *clone() override;

    void move(int dir) override;

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();
};