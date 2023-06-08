#pragma once

#include <memory>
#include <vector>
#include "CMap.h"

/**
 * @class CGameLayer
 * @brief Used to represent layers of the game, a base class for game layers.
 */
class CGameLayer {
public:
    virtual ~CGameLayer();

    virtual void UpdateLayer() = 0;

    virtual void DrawLayer() = 0;

    virtual std::shared_ptr<CMap> GetMap();

    virtual void SaveLayer();

protected:
    json LoadJsonFromFile(const std::string &filePath) const;
};
