#pragma once

#include "CEntity.h"
#include "CRigidBody.h"


class CPlayer : public CEntity {
public:
    CPlayer(std::shared_ptr<SParamLoader> params);

    void Draw() override;

    void Update(float deltaTime) override;

    void clean() override;

    void HandleInput(float deltaTime);

private:
    const int JUMP_FORCE = 10;
    const int JUMP_TIME = 15;
    const int MOVEMENT_SPEED = 3;
};