#include "CTimer.h"
#include "SDL2/SDL.h"

const int TARGET_FPS = 60;
const float TARGET_DELTA = 1.5F;

CTimer CTimer::m_Instance;

CTimer::CTimer() = default;


CTimer &CTimer::Instance() {
    return m_Instance;
}

float CTimer::GetDeltaTime() const {
    return m_DeltaTime;
}

void CTimer::Tick() {
    m_DeltaTime = (SDL_GetPerformanceCounter() - m_LastTime) * (TARGET_FPS / 1000.0F);
    if (m_DeltaTime > TARGET_DELTA)
        m_DeltaTime = TARGET_DELTA;
    m_LastTime = SDL_GetPerformanceCounter();
}
