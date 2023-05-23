#pragma once

#include "CEntity.h"
#include "CRigidBody.h"

class CPlayer : public CEntity {
public:
    CPlayer(std::shared_ptr<SParamLoader> params);

    void draw() override;

    void update(float deltaTime) override;

    void clean() override;

    void HandleInput();
};