#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>
#include "CMap.h"
#include "CTileLayer.h"
#include "CMapBackgroundLayer.h"

class CMapParser {
public:
    /**
     * @brief Parses the map.tmx file in the CGame::m_SourceSave directory.
     * @throws std::logic_error if map.tmx file is not found.
     */
    void Load();

    std::shared_ptr<CMap> GetMap(const std::string &id);

    CMapParser(const CMapParser &other) = delete;

    static CMapParser &Instance();

private:
    CMapParser();

    ~CMapParser();

    /**
     * @brief Parses the map.tmx file and extracts all attribute data required.
     * The parser is designed to handle .tmx files with multiple layers and tilesets.
     * @param name The name of the map to be used as a key in the m_Maps map.
     * @param source The location of the map.tmx file
     * @return
     */
    bool Parse(const char *name, const std::string &source);

    /**
     * @brief Parses a tileset from an XML node <tileset>.
     * This method extracts information about a tileset from the given XML node and
     * creates an STileSet object representing the tileset.
     * @param ptr The XML node representing the tileset.
     * @return The parsed STileSet object.
     */
    STileSet ParseTileSet(xmlNodePtr tileset);

    /**
     * @brief Parses a tile layer from an XML node <layer>.
     * This method extracts information about a tile layer from the given XML node.
     * The matrix on which the TileMap in CTileLayer is based is located in the <data>
     * child element of the <layer> element. Method parses this matrix from the <data> element
     * and stores it in a TileMap.
     * Creates a CTileLayer object representing the tile layer.
     * @param ptr The XML node representing the tile layer.
     * @param tileSets The shared pointer to the list of tile sets used in the map.
     * @param tileSize The size of each tile in pixels.
     * @param rowCount The number of rows in the tile layer.
     * @param colCount The number of columns in the tile layer.
     * @return The parsed CTileLayer object.
     * @throws std::logic_error if the XML node does not contain the required data element.
     */
    CTileLayer ParseTileLayer(xmlNodePtr ptr, std::shared_ptr<TilesetList> tileSets, int tileSize,
                              int rowCount, int colCount);

    std::string GetAttributeContent(xmlNodePtr ptr, const char *needle);

    std::map<std::string, std::shared_ptr<CMap>> m_Maps;

    static CMapParser m_Instance;

    /**
     * @brief Parses tilesets from the root XML node.
     * Each tileset is represented by the <tileset> node in the map.tmx file.
     * This method parses all tilesets from the given root XML node and adds them to
     * the specified tilesets list.
     * @param root The root XML node.
     * @param tileSets The shared pointer to the list of tile sets.
     */
    void ParseTilesets(xmlNodePtr root, std::shared_ptr<TilesetList> tileSets);

    /**
     * @brief Parses tile layers from the root XML node and adds them to the game map.
     * Each layer is represented by the <layer> element in the map.tmx file.
     * Creates CTileLayer objects for each layer. The parsed tile layers are then added to the provided game map.
     * @param root The root XML node.
     * @param tileSets The shared pointer to the list of tile sets used in the map.
     * @param tileWidth The width of each tile in pixels.
     * @param rowCount The number of rows in the tile layer.
     * @param colCount The number of columns in the tile layer.
     * @param gameMap The reference to the CMap object representing the game map.
     */
    void ParseTileLayers(xmlNodePtr root, std::shared_ptr<TilesetList> tileSets, int tileWidth,
                         int rowCount, int colCount, CMap &gameMap);
};

typedef CMapParser TheMapParser;