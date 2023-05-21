#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>
#include <string>
#include <vector>
#include "CMap.h"
#include "CMapLayer.h"
#include <memory>
#include "CTileSet.h"

class CMapParser {
public:
    bool Load();

    void Clean();

    std::shared_ptr<CMap> GetMaps();

    CMapParser(CMapParser &other) = delete;

    CMapParser &Instance() const;

private:
    bool Parse(std::string name, std::string source);

    CTileSet ParseTileSet(xmlNodePtr tileset);

    CMapParser();

    std::map<std::string, std::shared_ptr<CMap>> m_Maps;

    static CMapParser m_Instance;
};