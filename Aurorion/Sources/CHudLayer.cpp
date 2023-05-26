#include "CHudLayer.h"

void CHudLayer::DrawLayer() {
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), 255, 0, 0, 255);
    SDL_Rect a = {100, 100, 100, 100};
    SDL_RenderFillRect(TheGame::Instance().GetRenderer(), &a);
}

void CHudLayer::UpdateLayer(float deltaTime) {

}

