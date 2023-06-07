#pragma once

#include "CMapLayer.h"
#include "CTimer.h"
#include "STileSet.h"
#include <random>
#include <vector>
#include "EBlockType.h"

using TilesetList = std::vector<STileSet>;

/**
 * @brief Class representing a tile layer for a map.
 * Derived from CMapLayer base class and provides functionality
 * for managing a tile layer of a map. It handles rendering and updating of the tiles.
 */
class CTileLayer : public CMapLayer {
public:
    /**
     * @brief Constructor for the `CTileLayer` class.
     * @param tileSize The size of each tile in pixels.
     * @param rowCount The number of rows in the tile layer.
     * @param colCount The number of columns in the tile layer.
     * @param tileMap A shared pointer to the tile map data.
     * @param tileSets A shared pointer to the list of tileSets.
     */
    CTileLayer(int rowCount, int colCount, std::shared_ptr<TileMap> tileMap,
               std::shared_ptr<TilesetList> tileSets);

    /**
     * @brief Renders every tile on this map. Does calculation of the src_rect to be used
     * in the TheTextureManager::DrawTile method. This is done based on the position of the
     * tile in the matrix(m_TileMap).
     */
    void MapLayerRender() override;

    /**
     * @brief Updates the current state of the TileLayer. Manages the growth of mushrooms on the map
     * by generating a random x coordinate and checking if a mushroom can be placed on this x coordinate when
     * the timer runs out.
     */
    void MapLayerUpdate() override;

    /**
     * @brief Creates a copy of the XML file from which the game has been loaded from and replaces
     * the matrix in the <data> element with the current state of the map stored in m_TileMap.
     */
    void SaveMapLayer() override;

    std::shared_ptr<TileMap> GetTileMap() override;

private:
    int GenerateRandomCoordX() const;

    /**
     * @brief Finds the TileSet to which the tileId belongs to. Used in the MapLayerRender method.
     * @param tileId The tileId to be found.
     * @return TileSet to which the tileId belongs to.
     */
    const STileSet &FindTileSet(int tileId) const;

    const float GROW_TIME = 2000.0F;

    int m_RowCount;

    int m_ColCount;

    std::shared_ptr<TileMap> m_TileMap;

    std::shared_ptr<TilesetList> m_TileSets;

    float m_GrowTimer;
};
