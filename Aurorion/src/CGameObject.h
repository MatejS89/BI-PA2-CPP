#pragma once

#include "CGame.h"
#include "json.hpp"

using json = nlohmann::json;

/**
 * @class CGameObject
 * @brief The base class for game objects.
 */
class CGameObject {
public:
    virtual ~CGameObject();

    /**
     * @brief Draws the game object.
     */
    virtual void Draw() = 0;

    /**
     * @brief Updates the game object.
     * @return True if the update is successful, false otherwise.
     */
    virtual bool Update() = 0;

    virtual void ReduceHp(int dmg) = 0;

    virtual int GetCurrHp() const = 0;

    virtual int GetMaxHp() const = 0;

    /**
     * @brief Saves the game object to a JSON object.
     * @return The JSON representation of the game object.
     */
    virtual json Save() const = 0;

    /**
     * @brief Loads the game object from a JSON object.
     * @param jsonData The JSON data to load from.
     */
    virtual void Load(const json &jsonData) = 0;

    std::shared_ptr<CVector2D> GetCentre() const;

    virtual const SDL_Rect &GetCollider() const = 0;

protected:
    CGameObject();

    std::shared_ptr<CVector2D> m_Centre;
};
