#pragma once

#include "SDL2/SDL.h"
#include "CVector2D.h"
#include "CGame.h"
#include <memory>

class CCamera {
public:
    static CCamera &Instance();

    CCamera(const CCamera &other) = delete;

    void Update(float deltaTime);

    SDL_Rect &GetViewPort();

    CVector2D &GetPosition();

    void SetTarget(std::shared_ptr<CVector2D> target);

    std::shared_ptr<CVector2D> GetTarget() const;

private:
    CCamera();

    std::shared_ptr<CVector2D> m_Target;

    CVector2D m_Position;

    SDL_Rect m_ViewPort;

    static CCamera m_Instance;
};

typedef CCamera TheCamera;