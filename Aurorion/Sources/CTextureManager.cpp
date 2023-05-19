#include "CTextureManager.h"

CTextureManager CTextureManager::m_instance;

CTextureManager::CTextureManager() = default;

bool CTextureManager::Load(std::string fileName, std::string id, SDL_Renderer *renderer) {
    SDL_Surface *tmpSurface = IMG_Load(fileName.c_str());

    if (tmpSurface == nullptr)
        return false;

    SDL_Texture *texture =
            SDL_CreateTextureFromSurface(renderer, tmpSurface);

    SDL_FreeSurface(tmpSurface);

    if (texture != nullptr) {
        m_textureMap[id] = texture;
        return true;
    }
    return false;
}

void CTextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_Renderer *renderer,
                           SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;

    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;

    SDL_RenderCopyEx(renderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);

}

void CTextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                                SDL_Renderer *renderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = width;
    srcRect.h = height;

    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;
    SDL_RenderCopyEx(renderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

CTextureManager &CTextureManager::Instance() {
    return m_instance;
}

CTextureManager::~CTextureManager() {
    for (const auto &textureMap: m_textureMap) {
        SDL_DestroyTexture(textureMap.second);
    }
}
