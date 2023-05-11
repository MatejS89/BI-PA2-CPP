#pragma once

#include "CGame.h"

#include "SParamLoader.h"

class CGameObject {
public:
    virtual void draw() = 0;

    virtual void update() = 0;

    virtual void clean();

protected:
    CGameObject(const SParamLoader *params) {};

    virtual ~CGameObject();
};