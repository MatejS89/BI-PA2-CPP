#pragma once

#include "CEntity.h"
#include "CRigidBody.h"

#define JUMP_FORCE 10.0F
#define JUMP_TIME 15.0F

class CPlayer : public CEntity {
public:
    CPlayer(std::shared_ptr<SParamLoader> params);

    void Draw() override;

    void Update(float deltaTime) override;

    void clean() override;

    void HandleInput(float deltaTime);
};