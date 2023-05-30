#pragma once

#include <memory>
#include <map>
#include <string>
#include <functional>
#include "CPlayer.h"
#include "CEnemy.h"
#include "CGameObject.h"

class CGameObjectFactory {
    typedef std::function<std::shared_ptr<CGameObject>()> CreateObjectFunc;

public:
    void RegisterObject(const std::string &type, CreateObjectFunc func);

    static CGameObjectFactory &Instance();

    void RegisterObjects();

    std::shared_ptr<CGameObject> CreateGameObject(const std::string &type);

private:
    CGameObjectFactory();

    static CGameObjectFactory m_Instance;

    std::map<std::string, CreateObjectFunc> m_RegisteredObjects;
};

typedef CGameObjectFactory TheObjectFactory;