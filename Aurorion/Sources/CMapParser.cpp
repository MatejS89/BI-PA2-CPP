#include "CMapParser.h"

CMapParser CMapParser::m_Instance;

CMapParser &CMapParser::Instance() const {
    return m_Instance;
}

std::shared_ptr<CMap> CMapParser::GetMaps() {
    return std::shared_ptr<CMap>();
}
