#include "CMapParser.h"

CMapParser CMapParser::m_Instance;

CMapParser &CMapParser::Instance() {
    return m_Instance;
}

bool CMapParser::Load() {
    return Parse("MAP", "assets/map/map2.tmx");
}

bool CMapParser::Parse(const char *name, const char *source) {
    m_Source = source;
    xmlDocPtr doc = xmlReadFile(source, "UTF-8", 0);
    if (doc == nullptr) {
        std::cout << "FILE NOT READ" << std::endl;
        return false;
    }

    xmlNodePtr root = xmlDocGetRootElement(doc);
    int colCount = stoi(GetAttributeContent(root, "width"));
    int rowCount = stoi(GetAttributeContent(root, "height"));
    int tileWidth = stoi(GetAttributeContent(root, "tilewidth"));
    std::shared_ptr<TilesetList> tileSets = std::make_shared<TilesetList>();
    for (xmlNodePtr elem = xmlFirstElementChild(root); elem != nullptr; elem = xmlNextElementSibling(elem)) {
        if (xmlStrcmp(elem->name, reinterpret_cast<const xmlChar *> ("tileset")) == 0) {
            tileSets->push_back(ParseTileSet(elem));
        }
    }
    CMap gameMap;
    CMapBackgroundLayer backgroundLayer;
    gameMap.m_MapLayers.push_back(std::make_shared<CMapBackgroundLayer>(backgroundLayer));
    for (xmlNodePtr elem = xmlFirstElementChild(root); elem != nullptr; elem = xmlNextElementSibling(elem)) {
        if (xmlStrcmp(elem->name, reinterpret_cast<const xmlChar *> ("layer")) == 0) {
            CTileLayer layer = ParseTileLayer(elem, tileSets, tileWidth,
                                              rowCount, colCount);
            gameMap.m_MapLayers.push_back(std::make_shared<CTileLayer>(layer));
        }
    }
    gameMap.m_MapWidth = colCount * tileWidth;
    gameMap.m_MapHeight = rowCount * tileWidth;
    m_Maps[name] = std::make_shared<CMap>(gameMap);
    xmlFreeDoc(doc);
    return true;
}

STileSet CMapParser::ParseTileSet(xmlNodePtr ptr) {
    STileSet tileSet;
    tileSet.m_TileSetName = GetAttributeContent(ptr, "name");
    tileSet.m_FirstID = stoi(GetAttributeContent(ptr, "firstgid"));
    tileSet.m_TileSize = stoi(GetAttributeContent(ptr, "tilewidth"));
    tileSet.m_NumCol = stoi(GetAttributeContent(ptr, "columns"));
    tileSet.m_TileCount = stoi(GetAttributeContent(ptr, "tilecount"));
    tileSet.m_LastID = tileSet.m_FirstID + tileSet.m_TileCount - 1;
    tileSet.m_NumRows = tileSet.m_TileCount / tileSet.m_NumCol;
    xmlNodePtr image = xmlFirstElementChild(ptr);
    if (xmlStrcmp(image->name, reinterpret_cast<const xmlChar *> ("image")) == 0) {
        tileSet.m_TileSetSource = "assets/map/" + GetAttributeContent(image, "source");
    }
    return tileSet;
}

std::string CMapParser::GetAttributeContent(xmlNodePtr ptr, const char *needle) {
    xmlChar *content = xmlGetProp(ptr, reinterpret_cast<const xmlChar *>(needle));
    std::string contentStr = reinterpret_cast<const char *>(content);
    xmlFree(content);
    return contentStr;
}

CTileLayer CMapParser::ParseTileLayer(xmlNodePtr ptr, std::shared_ptr<TilesetList> tileSets,
                                      int tileSize, int rowCount, int colCount) {
    xmlNodePtr data = nullptr;
    for (xmlNodePtr elem = xmlFirstElementChild(ptr); elem != nullptr; elem = xmlNextElementSibling(elem)) {
        if (xmlStrcmp(elem->name, reinterpret_cast<const xmlChar *> ("data")) == 0) {
            data = elem;
            break;
        }
    }
    if (data == nullptr)
        throw std::logic_error("CHYBA");
    xmlChar *content = xmlNodeGetContent(data);

    std::shared_ptr<TileMap> tileMap = std::make_shared<TileMap>();

    std::string csvData(reinterpret_cast<char *>(content));
    std::stringstream ss(csvData);
    std::string token;

    while (std::getline(ss, token, '\n')) {
        std::stringstream row(token);
        std::string num;
        std::vector<int> rowData;
        while (std::getline(row, num, ',')) {
            rowData.push_back(stoi(num));
        }
        if (rowData.empty())
            continue;
        tileMap->push_back(rowData);
    }

    xmlFree(content);
    return CTileLayer(tileSize, rowCount, colCount, tileMap, tileSets);
}

std::shared_ptr<CMap> CMapParser::GetMaps(const std::string &id) {
    return m_Maps[id];
}

CMapParser::~CMapParser() {
    xmlCleanupParser();
}


CMapParser::CMapParser() = default;

