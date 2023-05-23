#pragma once

#include "CGame.h"

#include "SParamLoader.h"

class CGameObject {
public:
    virtual void draw() = 0;

    virtual void update(float deltaTime) = 0;

protected:
    CGameObject(std::shared_ptr<SParamLoader> params) {};

    virtual ~CGameObject();
};
