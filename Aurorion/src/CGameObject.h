#pragma once

#include "CGame.h"

#include "SParamLoader.h"

class CGameObject {
public:
    virtual ~CGameObject();

    virtual void Draw() = 0;

    virtual bool Update() = 0;

    virtual void ReduceHp(int dmg) = 0;

    virtual int GetCurrHp() const = 0;

    virtual int GetMaxHp() const = 0;

    virtual void Save() const = 0;

    std::shared_ptr<CVector2D> GetCentre();

    virtual const SDL_Rect &GetCollider() const = 0;

protected:
    CGameObject() {};

    std::shared_ptr<CVector2D> m_Centre;
};