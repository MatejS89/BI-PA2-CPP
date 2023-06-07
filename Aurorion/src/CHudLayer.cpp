#include "CHudLayer.h"

void CHudLayer::AddTarget(std::shared_ptr<CGameObject> target) {
    m_Target = target;
}

void CHudLayer::UpdateLayer() {
    float perc = static_cast<float>(m_Target->GetCurrHp()) / m_Target->GetMaxHp() * 100;
    m_CurrPerc = static_cast<int>(perc);
    if (m_CurrPerc <= 0)
        m_CurrPerc = 0;
}

void CHudLayer::DrawLayer() {
    SDL_Color tmp;
    SDL_GetRenderDrawColor(TheGame::Instance().GetRenderer(), &tmp.r, &tmp.g, &tmp.b, &tmp.a);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 255, 0, 0, 255);
    SDL_Rect a = {50, 50, m_CurrPerc, 10};
    SDL_RenderFillRect(TheGame::Instance().GetRenderer(), &a);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 128, 0, 0, 255);
    SDL_Rect b = {50 + m_CurrPerc, 50, 100 - m_CurrPerc, 10};
    SDL_RenderFillRect(TheGame::Instance().GetRenderer(), &b);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), tmp.r, tmp.g, tmp.b, tmp.a);
}
