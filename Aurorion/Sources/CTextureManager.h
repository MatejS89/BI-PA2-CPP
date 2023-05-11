#pragma once

#include <map>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "libxml/parser.h"

// singleton class
class CTextureManager {
public:
    bool Load(std::string fileName, std::string id, SDL_Renderer *renderer);

    void Draw(std::string id, int x, int y, int width, int height, SDL_Renderer *renderer,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

    void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                   SDL_Renderer *renderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    static CTextureManager *Instance();

private:
    CTextureManager();

    static CTextureManager *m_instance;

    std::map<std::string, SDL_Texture *> m_textureMap;
};

typedef CTextureManager TheTextureManager;
