#pragma once

#include "CGameObject.h"
#include "SParamLoader.h"
#include "CVector2D.h"

class CEntity : public CGameObject {
public:
    CEntity(const SParamLoader *params);

    virtual void draw();

    virtual void update();

    virtual void clean();

protected:
    CVector2D m_pos;
    CVector2D m_velocity;
    int m_W;
    int m_H;

    int m_currentRow;
    int m_currentFrame;

    std::string m_texture;
};