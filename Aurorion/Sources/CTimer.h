#pragma once

#include "SDL2/SDL.h"

class CTimer {
public:
    void Tick();

    float GetDeltaTime() const;

    static CTimer &Instance();

private:

    CTimer();

    static CTimer m_Instance;

    float m_DeltaTime;
    Uint64 m_LastTime;

    const int TARGET_FPS = 60;
    const float TARGET_DELTA = 1.5F;

};

typedef CTimer TheTimer;
