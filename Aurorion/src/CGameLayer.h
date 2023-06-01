#pragma once

#include <memory>
#include <vector>
#include "CMap.h"

class CGameLayer {

public:
    virtual void UpdateLayer() = 0;

    virtual void DrawLayer() = 0;

    virtual std::shared_ptr<CMap> GetMap();

    virtual void SaveLayer() = 0;

protected:
    json LoadJsonFromFile(const std::string &filePath) const;
};
