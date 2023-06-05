#pragma once

#include "SDL2/SDL.h"
#include "CVector2D.h"
#include "CGame.h"
#include <memory>

/**
 * @class CCamera
 * @brief Represents a camera object that can be used to view a scene.
 * The CCamera class provides functionality to control the position and target of a camera in a 2D space.
 * This is done to keep the target centered on screen.
 * It follows the singleton design pattern, allowing only a single instance of the camera to exist.
 */
class CCamera {
public:
    static CCamera &Instance();

    CCamera(const CCamera &other) = delete;

    /**
     * @brief Updates the camera state.
     * This method should be called to update the camera's position based on its target and any other necessary calculations
     * in order to keep the target centered on screen.
     */
    void Update();

    const CVector2D &GetPosition() const;

    void SetTarget(std::shared_ptr<CVector2D> target);

    std::shared_ptr<CVector2D> GetTarget() const;

private:
    CCamera();

    std::shared_ptr<CVector2D> m_Target;

    CVector2D m_Position;

    static CCamera m_Instance;
};

typedef CCamera TheCamera;