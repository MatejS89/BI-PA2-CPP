#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "CMap.h"
#include "CMapLayer.h"
#include "STileSet.h"
#include "CTileLayer.h"
#include <sstream>
#include <iostream>

class CMapParser {
public:
    bool Load();

    void Clean();

    std::shared_ptr<CMap> GetMaps(const std::string &id);

    CMapParser(CMapParser &other) = delete;

    static CMapParser &Instance();

private:
    bool Parse(const char *name, const char *source);

    STileSet ParseTileSet(xmlNodePtr tileset);

    CTileLayer ParseTileLayer(xmlNodePtr ptr, TilesetList tileSets, int tileSize,
                              int rowCount, int colCount);

    std::string GetAttributeContent(xmlNodePtr ptr, const char *needle);

    CMapParser();

    std::map<std::string, std::shared_ptr<CMap>> m_Maps;

    static CMapParser m_Instance;
};