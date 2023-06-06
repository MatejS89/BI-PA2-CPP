#pragma once

#include "CGameLayer.h"
#include "CGame.h"
#include "CGameObject.h"

/**
 * @class CHudLayer
 * @brief The class representing a hud layer, derived from CGameLayer.
 */
class CHudLayer : public CGameLayer {
public:
    /**
     * @brief Draws a HP bar in the left top corner of the screen.
     * The HP displayed is based on the percentage of current hp in relation to the maxHp of the target.
     */
    void DrawLayer() override;

    /**
     * @brief Adds a target to track the hp of.
     * @param target The desired target.
     */
    void AddTarget(std::shared_ptr<CGameObject> target);

    void UpdateLayer() override;

    void SaveLayer() override;

private:
    std::shared_ptr<CGameObject> m_Target;
};
