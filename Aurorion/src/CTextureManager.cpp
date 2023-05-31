#include "CTextureManager.h"

CTextureManager CTextureManager::m_instance;

CTextureManager::CTextureManager() = default;

bool CTextureManager::Load(const std::string &fileName, std::string id) {
    SDL_Surface *tmpSurface = IMG_Load(fileName.c_str());
    if (tmpSurface == nullptr)
        return false;

    SDL_Texture *texture =
            SDL_CreateTextureFromSurface(TheGame::Instance().GetRenderer(), tmpSurface);

    SDL_FreeSurface(tmpSurface);

    if (texture != nullptr) {
        m_textureMap[id] = texture;
        return true;
    }
    return false;
}

void CTextureManager::Draw(const std::string &id, int x, int y, int width, int height,
                           SDL_RendererFlip flip) {
    SDL_Rect srcRect{0, 0, width, height};
    SDL_Rect destRect{x, y, width, height};
    SDL_RenderCopyEx(TheGame::Instance().GetRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void
CTextureManager::DrawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentFrame,
                           SDL_RendererFlip flip) {
    const CVector2D &cam = TheCamera::Instance().GetPosition();
    SDL_Rect srcRect{width * currentFrame,
                     height * (currentRow - 1),
                     width, height};
    SDL_Rect destRect = {static_cast<int>(x - cam.GetX()), static_cast<int>(y - cam.GetY()), width, height};
    SDL_RenderCopyEx(TheGame::Instance().GetRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

CTextureManager &CTextureManager::Instance() {
    return m_instance;
}

void CTextureManager::DrawTile(const std::string &tileSetId, int tileSize, int x, int y, int row, int frame,
                               SDL_RendererFlip flip) {
    const CVector2D &cam = TheCamera::Instance().GetPosition();
    SDL_Rect destRect = {static_cast<int>(x - cam.GetX()), static_cast<int>(y - cam.GetY()), tileSize, tileSize};
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
    SDL_RenderCopyEx(TheGame::Instance().GetRenderer(), m_textureMap[tileSetId], &srcRect, &destRect, 0, 0, flip);
}

CTextureManager::~CTextureManager() = default;

void CTextureManager::Clean() {
    for (const auto &textureMap: m_textureMap) {
        SDL_DestroyTexture(textureMap.second);
    }
}
