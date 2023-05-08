#pragma once

#include "game.h"

class CTextureManager {
public:
    static SDL_Texture *LoadTexture(const char *fileName, SDL_Renderer *ren);
};
