#pragma once

#include "CEntity.h"

class CPlayer : public CEntity {
public:
    CPlayer(std::shared_ptr<SParamLoader> params);

    void draw() override;

    void update() override;

    void clean() override;

    void handleInput();
};