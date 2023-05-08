#include "CGameObject.h"
#include "texture_manager.h"

CGameObject::CGameObject(const char *texture, SDL_Renderer *renderer, int x, int y) : m_Renderer(renderer), m_xPos(x),
                                                                                      m_yPos(y), m_Width(64),
                                                                                      m_Height(64) {
    m_ObjTexture = CTextureManager::LoadTexture(texture, renderer);
}

CGameObject::~CGameObject() {}

void CGameObject::Update() {
    m_srcRect.h = m_Height;
    m_srcRect.w = m_Width;
    m_srcRect.x = 0;
    m_srcRect.y = 0;

    m_destRect.x = m_xPos;
    m_destRect.y = m_yPos;
    m_destRect.w = m_srcRect.w;
    m_destRect.h = m_srcRect.h;
}

void CGameObject::Render() {
    SDL_RenderCopy(m_Renderer, m_ObjTexture, &m_srcRect, &m_destRect);
}