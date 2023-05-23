#pragma once

#include "CEntity.h"
#include "CRigidBody.h"

class CPlayer : public CEntity {
public:
    CPlayer(std::shared_ptr<SParamLoader> params);

    void draw() override;

    void update() override;

    void clean() override;

    void HandleInput();

private:
    std::shared_ptr<CRigidBody> m_RigidBody;
};