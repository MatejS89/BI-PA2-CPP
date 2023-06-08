#pragma once

#include <memory>
#include <map>
#include <string>
#include <functional>
#include "CPlayer.h"
#include "CEnemy.h"

/**
 * @class CGameObjectFactory
 * @brief Singleton class for creating game objects of different types.
 */
class CGameObjectFactory {
    typedef std::function<std::shared_ptr<CGameObject>()> CreateObjectFunc;

public:
    /**
     * @brief Deleted copy constructor to prevent copying of CGameObjectFactory instances.
     */
    CGameObjectFactory(const CGameObjectFactory &other) = delete;

    static CGameObjectFactory &Instance();

    /**
    * @brief Registers a game object creation function for a given type.
    * @param type The type of the game object.
    * @param func The creation function for the game object.
    */
    void RegisterObject(const std::string &type, CreateObjectFunc func);

    /**
     * @brief Registers the available game objects.
     * This function should be called to register all the game objects that can be created.
     */
    void RegisterObjects();

    /**
     * @brief Creates a game object of the specified type.
     * @param type The type of the game object to create.
     * @return A shared pointer to the created game object, or nullptr if the type is not registered.
     */
    std::shared_ptr<CGameObject> CreateGameObject(const std::string &type);

private:
    CGameObjectFactory();

    ~CGameObjectFactory();

    static CGameObjectFactory m_Instance;

    std::map<std::string, CreateObjectFunc> m_RegisteredObjects;
};

typedef CGameObjectFactory TheObjectFactory;