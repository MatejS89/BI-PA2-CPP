#pragma once

#include "string"

struct SParamLoader {
    SParamLoader(float xPos, float yPos, int width, int height, std::string texture);

protected:
    float m_X;
    float m_Y;
    int m_W;
    int m_H;

    std::string m_texture;

    friend class CGameObject;

    friend class CEntity;
};