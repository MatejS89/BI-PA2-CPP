#pragma once

#include <string>
#include <vector>
#include <map>

struct STileSet {

    std::string m_TileSetName;

    std::string m_TileSetSource;

    int m_FirstID;

    int m_LastID;

    int m_NumRows;

    int m_NumCol;

    int m_TileCount;

    int m_TileSize;
};