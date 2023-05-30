#pragma once

#include "string"

struct SParamLoader {
    SParamLoader(int xPos, int yPos, int width, int height, std::string texture);

protected:
    int m_X;
    int m_Y;
    int m_W;
    int m_H;

    std::string m_texture;

    friend class CGameObject;

    friend class CEntity;
};