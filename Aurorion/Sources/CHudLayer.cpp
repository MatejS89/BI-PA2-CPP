#include "CHudLayer.h"

void CHudLayer::DrawLayer() {
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 255, 0, 0, 255);
    float perc = static_cast<float>(m_Target->GetCurrHp()) / m_Target->GetMaxHp() * 100;
    int curr = static_cast<int>(perc);
//    std::cout << m_Target->GetCurrHp() << "   " << m_Target->GetMaxHp() << "  " << curr << std::endl;
    SDL_Rect a = {50, 50, curr, 10};
    SDL_RenderFillRect(TheGame::Instance().GetRenderer(), &a);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 255, 155, 0, 255);
    SDL_Rect b = {50 + curr, 50, 100 - curr, 10};
    SDL_RenderFillRect(TheGame::Instance().GetRenderer(), &b);
}

void CHudLayer::UpdateLayer(float deltaTime) {
}

void CHudLayer::AddTarget(std::shared_ptr<CPlayer> target) {
    m_Target = target;
}
