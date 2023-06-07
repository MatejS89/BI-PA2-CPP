#pragma once

#include "SDL2/SDL.h"

/**
 * @class CTimer
 * @brief Manages the game timer and provides timing-related functionality.
 */
class CTimer {
public:
    /**
     * @brief Deleted copy constructor to prevent copying of CTimer instances.
     */
    CTimer(const CTimer &other) = delete;

    /**
     * @brief Updates the timer, calculating the delta time since the last tick.
     */
    void Tick();

    float GetDeltaTime() const;

    int GetTargetFps() const;

    static CTimer &Instance();

private:
    CTimer();

    ~CTimer();

    static CTimer m_Instance;

    float m_DeltaTime;

    Uint64 m_LastTime;

    const int TARGET_FPS = 60;

    const float TARGET_DELTA = 1.5F;
};

typedef CTimer TheTimer;
