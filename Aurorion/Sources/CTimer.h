#pragma once

class CTimer {
public:
    void Tick();

    float GetDeltaTime() const;

    static CTimer &Instance();

private:

    CTimer();

    static CTimer m_Instance;

    float m_DeltaTime;
    float m_LastTime;
};

typedef CTimer TheTimer;
