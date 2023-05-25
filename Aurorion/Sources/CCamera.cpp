#include "CCamera.h"

CCamera CCamera::m_Instance;

CCamera &CCamera::Instance() {
    return m_Instance;
}

CCamera::CCamera() = default;

CVector2D &CCamera::GetPosition() {
    return m_Position;
}

SDL_Rect &CCamera::GetViewPort() {
    return m_ViewPort;
}

void CCamera::SetTarget(std::shared_ptr<CVector2D> target) {
    m_ViewPort.w = TheGame::Instance().GetWindowWidth();
    m_ViewPort.h = TheGame::Instance().GetWindowHeight();
    m_Target = target;
}

void CCamera::Update(float deltaTime) {
    if (m_Target == nullptr)
        return;

    m_ViewPort.x = m_Target->GetX() - TheGame::Instance().GetWindowWidth() / 2;
    m_ViewPort.y = m_Target->GetY() - TheGame::Instance().GetWindowHeight() / 2;

    if (m_ViewPort.x < 0)
        m_ViewPort.x = 0;

    if (m_ViewPort.y < 0)
        m_ViewPort.y = 0;

//    if (m_ViewPort.x > (2 * TheGame::Instance().GetWindowWidth() - m_ViewPort.w))
//        m_ViewPort.x = (2 * TheGame::Instance().GetWindowWidth() - m_ViewPort.w);

    if (m_ViewPort.y > (2 * TheGame::Instance().GetWindowHeight() - m_ViewPort.h))
        m_ViewPort.y = (2 * TheGame::Instance().GetWindowHeight() - m_ViewPort.h);

    if (m_ViewPort.x > TheGame::Instance().GetMapWidth() - TheGame::Instance().GetWindowWidth())
        m_ViewPort.x = TheGame::Instance().GetMapWidth() - TheGame::Instance().GetWindowWidth();

    m_Position = {m_ViewPort.x, m_ViewPort.y};
//    std::cout << "TARGET : " << m_Target->GetX() << " " << m_Target->GetY() << std::endl;
//    std::cout << "VIEW : " << m_ViewPort.x << " " << m_ViewPort.y << std::endl;
//    std::cout << "POS: " << m_Position.GetX() << m_Position.GetY() << std::endl;
}
