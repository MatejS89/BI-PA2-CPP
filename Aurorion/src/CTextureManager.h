#pragma once

#include <map>
#include <string>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "CGame.h"
#include "CCamera.h"

/**
 * @class CTextureManager
 * @brief Singleton class, handles loading and rendering of textures.
 * The CTextureManager class is responsible for loading and managing textures for rendering.
 * It uses the SDL library for texture operations.
 */
class CTextureManager {
public:
    /**
     * @brief Deleted copy constructor to prevent copying of CTextureManager objects.
     */
    CTextureManager(const CTextureManager &other) = delete;

    /**
     * @brief Loads a texture from a file.
     * Creates a SDL_texture and associates it with an id and stores it in a map (m_TextureMap).
     * @param fileName The path to the texture file.
     * @param id The ID to associate with the loaded texture.
     * @return True if the texture was successfully loaded, false otherwise.
     */
    bool Load(const std::string &fileName, std::string id);

    /**
     * @brief Draws a tile from a tileset texture.
     * Draws a specific tile from a tileset texture at the specified position.
     * @param tileSetId The ID of the tileset texture.
     * @param tileSize The size of each tile.
     * @param x The x position to draw the tile.
     * @param y The y position to draw the tile.
     * @param row The row index of the tile in the tileset.
     * @param frame The frame index of the tile in the tileset.
     * @param flip The flip mode for the texture rendering.
     */
    void DrawTile(const std::string &tileSetId, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip);

    /**
     * @brief Draws a frame from a texture which represents a spritesheet.
     * Draws a specific frame from a texture at the specified position and size.
     * @param id The ID of the texture.
     * @param x The x position to draw the frame.
     * @param y The y position to draw the frame.
     * @param width The width of the frame.
     * @param height The height of the frame.
     * @param currentRow The row index of the frame in the texture.
     * @param currentFrame The frame index of the frame in the texture.
     * @param flip The flip mode for the texture rendering.
     */
    void DrawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentFrame,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    static CTextureManager &Instance();

    /**
     * @brief This method releases all loaded textures used by the texture manager.
     */
    void Clean();

private:
    CTextureManager();

    ~CTextureManager();

    static CTextureManager m_Instance;

    std::map<std::string, SDL_Texture *> m_TextureMap;
};

typedef CTextureManager TheTextureManager;
