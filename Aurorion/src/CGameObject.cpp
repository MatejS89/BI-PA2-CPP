#include "CGameObject.h"

CGameObject::~CGameObject() = default;

std::shared_ptr<CVector2D> CGameObject::GetCentre() {
    return m_Centre;
}
