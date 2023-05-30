#include "CGameObjectFactory.h"

CGameObjectFactory CGameObjectFactory::m_Instance;

CGameObjectFactory &CGameObjectFactory::Instance() {
    return m_Instance;
}

void CGameObjectFactory::RegisterObject(const std::string &type, CGameObjectFactory::CreateObjectFunc func) {
    m_RegisteredObjects[type] = func;
}

std::shared_ptr<CGameObject> CGameObjectFactory::CreateGameObject(const std::string &type) {
    auto it = m_RegisteredObjects.find(type);
    if (it == m_RegisteredObjects.end())
        return nullptr;
    return it->second();
}

void CGameObjectFactory::RegisterObjects() {
    RegisterObject("CPlayer", CPlayer::Create);
}

CGameObjectFactory::CGameObjectFactory() = default;
