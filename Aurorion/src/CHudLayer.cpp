#include "CHudLayer.h"

void CHudLayer::DrawLayer() {
    SDL_Color tmp;
    SDL_GetRenderDrawColor(TheGame::Instance().GetRenderer(), &tmp.r, &tmp.g, &tmp.b, &tmp.a);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 255, 0, 0, 255);
    float perc = static_cast<float>(m_Target->GetCurrHp()) / m_Target->GetMaxHp() * 100;
    int currHp = static_cast<int>(perc);
    if (currHp <= 0)
        currHp = 0;
    SDL_Rect a = {50, 50, currHp, 10};
    SDL_RenderFillRect(TheGame::Instance().GetRenderer(), &a);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 128, 0, 0, 255);
    SDL_Rect b = {50 + currHp, 50, 100 - currHp, 10};
    SDL_RenderFillRect(TheGame::Instance().GetRenderer(), &b);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), tmp.r, tmp.g, tmp.b, tmp.a);
}

void CHudLayer::UpdateLayer() {
    return;
}

void CHudLayer::AddTarget(std::shared_ptr<CGameObject> target) {
    m_Target = target;
}

void CHudLayer::SaveLayer() {
    return;
}
