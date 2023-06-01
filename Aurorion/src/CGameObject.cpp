#include "CGameObject.h"

CGameObject::~CGameObject() = default;

std::shared_ptr<CVector2D> CGameObject::GetCentre() const {
    return m_Centre;
}

CGameObject::CGameObject() : m_Centre(std::make_shared<CVector2D>(0, 0)) {}
