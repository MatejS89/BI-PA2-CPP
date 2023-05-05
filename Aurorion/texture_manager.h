#include "game.h"

#ifndef AURORION_TEXTURE_MANAGER_H
#define AURORION_TEXTURE_MANAGER_H

class TextureManager {
public:
    static SDL_Texture *LoadTexture(const char *fileName, SDL_Renderer *ren);
};

#endif //AURORION_TEXTURE_MANAGER_H
