#include "CTextureManager.h"

CTextureManager CTextureManager::m_Instance;

CTextureManager::CTextureManager() = default;

bool CTextureManager::Load(const std::string &fileName, std::string id) {
    SDL_Surface *tmpSurface = IMG_Load(fileName.c_str());
    if (tmpSurface == nullptr)
        return false;

    SDL_Texture *texture =
            SDL_CreateTextureFromSurface(TheGame::Instance().GetRenderer(), tmpSurface);

    SDL_FreeSurface(tmpSurface);

    if (texture != nullptr) {
        m_TextureMap[id] = texture;
        return true;
    }
    return false;
}

void CTextureManager::DrawFrame(const std::string &id, int x, int y, int width, int height, int currentRow,
                                int currentFrame, SDL_RendererFlip flip) {
    const CVector2D &cam = TheCamera::Instance().GetPosition();
    SDL_Rect srcRect{width * currentFrame,
                     height * (currentRow - 1),
                     width, height};
    SDL_Rect destRect = {static_cast<int>(x - cam.GetX()), static_cast<int>(y - cam.GetY()), width, height};
    SDL_RenderCopyEx(TheGame::Instance().GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

CTextureManager &CTextureManager::Instance() {
    return m_Instance;
}

void CTextureManager::DrawTile(const std::string &tileSetId, int tileSize, int x, int y, int row, int frame,
                               SDL_RendererFlip flip) {
    const CVector2D &cam = TheCamera::Instance().GetPosition();
    SDL_Rect destRect = {static_cast<int>(x - cam.GetX()), static_cast<int>(y - cam.GetY()), tileSize, tileSize};
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
    SDL_RenderCopyEx(TheGame::Instance().GetRenderer(), m_TextureMap[tileSetId], &srcRect, &destRect, 0, 0, flip);
}

CTextureManager::~CTextureManager() = default;

void CTextureManager::Clean() {
    for (const auto &texture: m_TextureMap) {
        SDL_DestroyTexture(texture.second);
    }
}
