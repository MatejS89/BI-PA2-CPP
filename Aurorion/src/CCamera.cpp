#include "CCamera.h"

CCamera::CCamera() = default;

CCamera CCamera::m_Instance;

CCamera &CCamera::Instance() {
    return m_Instance;
}

void CCamera::Update() {
    if (m_Target == nullptr)
        return;

    m_Position.SetX(m_Target->GetX() - TheGame::Instance().GetWindowWidth() / 2);
    m_Position.SetY(m_Target->GetY() - TheGame::Instance().GetWindowHeight() / 2);

    if (m_Position.GetX() < 0)
        m_Position.SetX(0);

    if (m_Position.GetY() < 0)
        m_Position.SetY(0);

    if (m_Position.GetY() > TheGame::Instance().GetWindowHeight())
        m_Position.SetY(TheGame::Instance().GetWindowHeight());

    if (m_Position.GetX() > TheGame::Instance().GetMapWidth() - TheGame::Instance().GetWindowWidth())
        m_Position.SetX(TheGame::Instance().GetMapWidth() - TheGame::Instance().GetWindowWidth());
}

const CVector2D &CCamera::GetPosition() const {
    return m_Position;
}

void CCamera::SetTarget(std::shared_ptr<CVector2D> target) {
    m_Target = target;
}

std::shared_ptr<CVector2D> CCamera::GetTarget() const {
    return m_Target;
}
