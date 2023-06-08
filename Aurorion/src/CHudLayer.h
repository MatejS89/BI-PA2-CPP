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
    CHudLayer();

    ~CHudLayer() override;

    /**
     * @brief Adds a target to track the hp of.
     * @param target The desired target.
     */
    void AddTarget(std::shared_ptr<CGameObject> target);

    /**
     * @brief Calculates the percentage of current hp of the target in relation to the max hp of the target.
     * Stores the current percentage in m_CurrPerc
     */
    void UpdateLayer() override;

    /**
     * @brief Draws a HP bar in the left top corner of the screen.
     * The HP displayed is based on m_CurrPerc.
     */
    void DrawLayer() override;

private:
    std::shared_ptr<CGameObject> m_Target;

    int m_CurrPerc;
};
