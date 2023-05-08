#pragma once

#include <map>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// singleton class
class CTextureManager {
public:
    bool Load(std::string fileName, std::string id, SDL_Renderer *renderer);

    void Draw(std::string id, int x, int y, int width, int height, SDL_Renderer *renderer,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

    void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                   SDL_Renderer *renderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    static CTextureManager *Instance() {
        if (m_Instance == nullptr) {
            m_Instance = new CTextureManager();
            return m_Instance;
        }
        return m_Instance;
    }

private:
    CTextureManager();

    static CTextureManager *m_Instance;

    std::map<std::string, SDL_Texture *> m_textureMap;
};