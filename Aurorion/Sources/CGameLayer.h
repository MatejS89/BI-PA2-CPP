#pragma once

#include <memory>
#include <vector>
#include "CMap.h"

class CGameLayer {

public:

    virtual void UpdateLayer(float deltaTime) = 0;

    virtual void DrawLayer() = 0;

    virtual std::shared_ptr<CMap> GetMap();
};
