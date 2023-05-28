#include "CMapBackgroundLayer.h"

std::shared_ptr<TileMap> CMapBackgroundLayer::GetTileMap() {
    return nullptr;
}

void CMapBackgroundLayer::LayerUpdate() {
    if (m_StateTimer <= 0) {
        SDL_Color tmp;
        SDL_GetRenderDrawColor(TheGame::Instance().GetRenderer(), &tmp.r, &tmp.g, &tmp.b, &tmp.a);
        std::cout << static_cast<int>(tmp.r) << " " << static_cast<int>(tmp.g) << " " << static_cast<int>(tmp.b)
                  << std::endl;
        if (IsDay(tmp)) {
            std::cout << "SWITCH" << std::endl;
            NextState();
        } else if (IsNight(tmp))
            NextState();
        switch (m_BackgroundState) {
            case BackgroundState::NIGHT:
                std::cout << "TONIGHT" << std::endl;
                ChangeIntoDay(tmp);
                break;
            case BackgroundState::DAY:
                std::cout << "TODAY" << std::endl;
                ChangeIntoNight(tmp);
                break;
            default:
                break;
        }
        m_StateTimer = STATE_TIME;
    } else {
        m_StateTimer -= TheTimer::Instance().GetDeltaTime();
    }
}

void CMapBackgroundLayer::LayerRender() {
}

CMapBackgroundLayer::CMapBackgroundLayer() : m_BackgroundState(BackgroundState::DAY), m_StateTimer(0) {
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), TARGET_COLOR.r, TARGET_COLOR.g, TARGET_COLOR.b,
                           TARGET_COLOR.a);
}

void CMapBackgroundLayer::NextState() {
    switch (m_BackgroundState) {
        case BackgroundState::DAY:
            m_BackgroundState = BackgroundState::NIGHT;
            break;
        case BackgroundState::NIGHT:
            m_BackgroundState = BackgroundState::DAY;
            break;
        default:
            break;
    }
}

void CMapBackgroundLayer::ChangeIntoDay(SDL_Color &tmp) {
    int stepR = floor(tmp.r / TRANSFORM);
    int stepG = floor(tmp.g / TRANSFORM);
    int stepB = floor(tmp.b / TRANSFORM);
    GraduallyDecrease(tmp);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), tmp.r - stepR, tmp.g - stepG, tmp.b - stepB, tmp.a);
}

void CMapBackgroundLayer::ChangeIntoNight(SDL_Color &tmp) {
    int stepR = floor(TARGET_COLOR.r / TRANSFORM);
    int stepG = floor(TARGET_COLOR.g / TRANSFORM);
    int stepB = floor(TARGET_COLOR.b / TRANSFORM);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), tmp.r + stepR, tmp.g + stepG, tmp.b + stepB, tmp.a);
}

bool CMapBackgroundLayer::IsNight(const SDL_Color &tmp) {
    return (tmp.r == 0 && tmp.b == 0 &&
            tmp.g == 0);
}

bool CMapBackgroundLayer::IsDay(const SDL_Color &tmp) {
    return (tmp.r == TARGET_COLOR.r &&
            tmp.g == TARGET_COLOR.g &&
            tmp.b == TARGET_COLOR.b);
}

void CMapBackgroundLayer::GraduallyDecrease(SDL_Color &tmp) {
    if (tmp.r == tmp.g && tmp.g == tmp.b) {
        tmp.r -= 1;
        tmp.g -= 1;
        tmp.b -= 1;
    }
}
