#pragma once

#include "CGame.h"

#include "SParamLoader.h"

class CGameObject {
public:
    virtual void Draw() = 0;

    virtual bool Update() = 0;

    virtual void ReduceHp(int dmg) = 0;

    std::shared_ptr<CVector2D> GetCentre();

    virtual const SDL_Rect &GetCollider() const;

protected:
    CGameObject(std::shared_ptr<SParamLoader> params) {};

    std::shared_ptr<CVector2D> m_Centre;

    virtual ~CGameObject();
};
