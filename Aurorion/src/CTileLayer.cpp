#include "CTileLayer.h"

#include "CTextureManager.h"
#include "CGame.h"
#include <iostream>
#include <fstream>
#include <string>

CTileLayer::CTileLayer(int tileSize, int rowCount, int colCount,
                       std::shared_ptr<TileMap> tileMap, std::shared_ptr<TilesetList> tileSets) :
        m_TileSize(tileSize), m_RowCount(rowCount),
        m_ColCount(colCount), m_TileMap(tileMap),
        m_TileSets(tileSets),
        m_GrowDelay(0.0F) {
    for (const auto &item: *m_TileSets) {
        TheTextureManager::Instance().Load(item.m_TileSetSource, item.m_TileSetName);
    }
}

void CTileLayer::LayerRender() {
    for (int i = 0; i < m_RowCount; i++) {
        for (int j = 0; j < m_ColCount; j++) {
            int tileId = (*m_TileMap)[i][j];
            if (tileId == 0)
                continue;
            STileSet tileSet = FindTileSet(tileId);
            int tileRow = tileId / tileSet.m_NumCol;
            int tileCol = tileId % tileSet.m_NumCol - 1;
            if (tileCol < 0) {
                tileRow--;
                tileCol = tileSet.m_NumCol - 1;
            }
            TheTextureManager::Instance().DrawTile(tileSet.m_TileSetName, tileSet.m_TileSize,
                                                   j * tileSet.m_TileSize, i * tileSet.m_TileSize, tileRow, tileCol,
                                                   SDL_FLIP_NONE);
        }
    }
}


const STileSet &CTileLayer::FindTileSet(int tileId) const {
    for (const auto &tileSet: *m_TileSets) {
        if (tileId >= tileSet.m_FirstID && tileId <= tileSet.m_LastID) {
            return tileSet;
        }
    }
    throw std::runtime_error("Tile set not found for tileId: " + std::to_string(tileId));
}

void CTileLayer::LayerUpdate() {
    if (m_GrowDelay <= 0) {
        m_GrowDelay = GROW_TIME;
        int xCoord = floor(GenerateRandomCoordX() / m_TileSize);
        for (int i = floor(TheGame::Instance().GetMapHeight() / m_TileSize) - 1; i >= 0; i--) {
            auto &currentTile = (*m_TileMap)[i][xCoord];
            if (currentTile == LAVA || currentTile == WATER)
                break;
            if (currentTile == EMPTY) {
                currentTile = MUSHROOM;
                break;
            }
        }
    } else
        m_GrowDelay -= TheTimer::Instance().GetDeltaTime();
}

std::shared_ptr<TileMap> CTileLayer::GetTileMap() {
    return m_TileMap;
}

int CTileLayer::GenerateRandomCoordX() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, TheGame::Instance().GetMapWidth());
    return distribution(gen);
}

void CTileLayer::SaveMapLayer() {
    std::string inputFile = "assets/map/tmp.tmx";
    std::string outputFile = "assets/map/tmp3.tmx";

    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (inFile.is_open() && outFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line) && inFile.good() && outFile.good()) {
            if (line.find("<data encoding=\"csv\">") != std::string::npos) {
                outFile << line << "\n";
                std::getline(inFile, line);
                for (const auto &row: *m_TileMap) {
                    for (const auto &num: row) {
                        outFile << num;
//                        if (row != m_TileMap->back() && num != row.back())
                        outFile << ",";
                    }
                    outFile << '\n';
                }
                while (std::getline(inFile, line) && line != "</data>") {}
                outFile << line << "\n";
            } else {
                outFile << line << "\n";
            }
        }
        inFile.close();
        outFile.close();
    }
}