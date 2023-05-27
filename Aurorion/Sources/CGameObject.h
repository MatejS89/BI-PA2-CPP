#pragma once

#include "CGame.h"

#include "SParamLoader.h"

class CGameObject {
public:
    virtual void Draw() = 0;

    virtual bool Update(float deltaTime) = 0;

    std::shared_ptr<CVector2D> GetCentre();

protected:
    CGameObject(std::shared_ptr<SParamLoader> params) {};

    std::shared_ptr<CVector2D> m_Centre;

    virtual ~CGameObject();
};
