#pragma once

#include "CEntity.h"
#include "CRigidBody.h"
#include "CCamera.h"


class CEnemy : public CEntity {
public:
    CEnemy(std::shared_ptr<SParamLoader> params);

    void Draw() override;

    void Update(float deltaTime) override;

    void clean() override;

private:
    const int JUMP_FORCE = 10;
    const int JUMP_TIME = 15;
    const float MOVEMENT_SPEED = 1.5F;
    const int RADIUS = 200;
};
