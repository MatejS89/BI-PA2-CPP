#include "CMapBackgroundLayer.h"

std::shared_ptr<TileMap> CMapBackgroundLayer::GetTileMap() {
    return nullptr;
}

void CMapBackgroundLayer::LayerUpdate() {
    if (m_StateTimer <= 0) {
        SDL_Color tmp;
        SDL_GetRenderDrawColor(TheGame::Instance().GetRenderer(), &tmp.r, &tmp.g, &tmp.b, &tmp.a);
        if (IsDay(tmp) || IsNight(tmp))
            NextState();
        switch (m_BackgroundState) {
            case BackgroundState::NIGHT:
                ChangeIntoDay(tmp);
                break;
            case BackgroundState::DAY:
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
    int stepR = floor(tmp.r / GRADIENT);
    int stepG = floor(tmp.g / GRADIENT);
    int stepB = floor(tmp.b / GRADIENT);
    GraduallyDecrease(tmp);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), tmp.r - stepR, tmp.g - stepG, tmp.b - stepB, tmp.a);
}

void CMapBackgroundLayer::ChangeIntoNight(SDL_Color &tmp) {
    int stepR = floor(TARGET_COLOR.r / GRADIENT);
    int stepG = floor(TARGET_COLOR.g / GRADIENT);
    int stepB = floor(TARGET_COLOR.b / GRADIENT);
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

void CMapBackgroundLayer::SaveMapLayer() {
    json jsonData;
    jsonData["GRADIENT"] = GRADIENT;
    jsonData["STATE_TIME"] = STATE_TIME;
    jsonData["STATE_TIMER"] = m_StateTimer;
    jsonData["TARGET_COLOR.R"] = TARGET_COLOR.r;
    jsonData["TARGET_COLOR.G"] = TARGET_COLOR.g;
    jsonData["TARGET_COLOR.B"] = TARGET_COLOR.g;
    jsonData["TARGET_COLOR.A"] = TARGET_COLOR.a;
    std::ofstream file("examples/NewGame/BackGroundLayer.json");
    if (file.is_open()) {
        file << jsonData.dump(4);
        file.close();
    } else
        throw std::logic_error("Failed to save GameObjects");
}
