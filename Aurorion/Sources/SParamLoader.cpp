#include "SParamLoader.h"

SParamLoader::SParamLoader(int xPos, int yPos, int width, int height, std::string texture) :
        m_X(xPos), m_Y(yPos), m_W(width), m_H(height), m_texture(std::move(texture)) {}
