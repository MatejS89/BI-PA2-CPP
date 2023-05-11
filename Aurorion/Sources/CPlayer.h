#pragma once

#include "CEntity.h"

class CPlayer : public CEntity {
public:
    CPlayer(const SParamLoader *params);

    void draw() override;

    void update() override;

    void clean() override;
};