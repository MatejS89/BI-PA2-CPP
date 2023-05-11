#pragma once

#include "CGameObject.h"
#include "SParamLoader.h"

class CEntity : public CGameObject {
public:
    CEntity(const SParamLoader *params);

    void draw();

    virtual void update();

    virtual void clean();

protected:
    int m_X;
    int m_Y;
    int m_W;
    int m_H;

    int m_currentRow;
    int m_currentFrame;

    std::string m_texture;
};