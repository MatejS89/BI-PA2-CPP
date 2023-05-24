#pragma once

#include "CGame.h"

#include "SParamLoader.h"

class CGameObject {
public:
    virtual void draw() = 0;

    virtual void update(float deltaTime) = 0;

    std::shared_ptr<CVector2D> GetCentre();

protected:
    CGameObject(std::shared_ptr<SParamLoader> params) {};

    std::shared_ptr<CVector2D> m_Centre;

    virtual ~CGameObject();
};
