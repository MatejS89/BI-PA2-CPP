#pragma once

#include "CGameObject.h"
#include "SParamLoader.h"
#include "CVector2D.h"
#include "CRigidBody.h"

class CEntity : public CGameObject {
public:
    CEntity(std::shared_ptr<SParamLoader> params);

    virtual void draw();

    virtual void update(float deltaTime);

    virtual void clean();

    std::shared_ptr<CVector2D> GetPosition();

protected:
    int m_W;
    int m_H;

    int m_currentRow;
    int m_currentFrame;

    std::string m_texture;

    std::shared_ptr<CRigidBody> m_RigidBody;
};