#pragma once

#include <map>
#include <string>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "CGame.h"

// singleton class
class CTextureManager {
public:
    CTextureManager(const CTextureManager &other) = delete;

    ~CTextureManager();

    bool Load(const std::string &fileName, std::string id);

    void Draw(const std::string &id, int x, int y, int width, int height,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

    void DrawTile(const std::string &tileSetId, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip);

    void DrawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentFrame,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    static CTextureManager &Instance();

    void AddRenderer(SDL_Renderer *renderer);

private:
    CTextureManager();

    SDL_Renderer *m_Renderer;

    static CTextureManager m_instance;

    std::map<std::string, SDL_Texture *> m_textureMap;
};

typedef CTextureManager TheTextureManager;
