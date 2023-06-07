#include "CMapBackgroundLayer.h"

CMapBackgroundLayer::CMapBackgroundLayer() = default;

void CMapBackgroundLayer::MapLayerUpdate() {
    if (m_StateTimer <= 0) {
        switch (m_BackgroundState) {
            case BackgroundState::DAY:
                ChangeIntoNight();
                break;
            case BackgroundState::NIGHT:
                ChangeIntoDay();
                break;
            default:
                break;
        }
        m_StateTimer = STATE_TIME;
        if (IsDay() || IsNight())
            NextState();
    } else {
        m_StateTimer -= TheTimer::Instance().GetDeltaTime();
    }
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

void CMapBackgroundLayer::ChangeIntoNight() {
    Uint8 currR = m_CurrColor.r - floor(m_CurrColor.r / GRADIENT);
    Uint8 currG = m_CurrColor.g - floor(m_CurrColor.g / GRADIENT);
    Uint8 currB = m_CurrColor.b - floor(m_CurrColor.b / GRADIENT);
    m_CurrColor = {currR, currG, currB, m_CurrColor.a};
    GraduallyDecrease();
//    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), m_CurrColor.r, m_CurrColor.g, m_CurrColor.b,
//                           m_CurrColor.a);
}

void CMapBackgroundLayer::ChangeIntoDay() {
    Uint8 currR = m_CurrColor.r + floor(TARGET_COLOR.r / GRADIENT);
    Uint8 currG = m_CurrColor.g + floor(TARGET_COLOR.g / GRADIENT);
    Uint8 currB = m_CurrColor.b + floor(TARGET_COLOR.b / GRADIENT);
    m_CurrColor = {currR, currG, currB, m_CurrColor.a};
//    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), m_CurrColor.r, m_CurrColor.g, m_CurrColor.b,
//                           m_CurrColor.a);
}

bool CMapBackgroundLayer::IsNight() {
    return (m_CurrColor.r <= 30 && m_CurrColor.b <= 30 &&
            m_CurrColor.g <= 30);
}

bool CMapBackgroundLayer::IsDay() {
    return (m_CurrColor.r >= TARGET_COLOR.r &&
            m_CurrColor.g >= TARGET_COLOR.g &&
            m_CurrColor.b >= TARGET_COLOR.b);
}

void CMapBackgroundLayer::GraduallyDecrease() {
    if (m_CurrColor.r < GRADIENT && m_CurrColor.g < GRADIENT && m_CurrColor.b < GRADIENT) {
        m_CurrColor.r -= 1;
        m_CurrColor.g -= 1;
        m_CurrColor.b -= 1;
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
    jsonData["CURR_COLOR.R"] = m_CurrColor.r;
    jsonData["CURR_COLOR.G"] = m_CurrColor.g;
    jsonData["CURR_COLOR.B"] = m_CurrColor.b;
    std::ofstream file(TheGame::Instance().GetNextSaveDir() + "BackGroundLayer.json");
    if (file.is_open()) {
        file << jsonData.dump(4);
        file.close();
    } else
        throw std::logic_error("Failed to save GameObjects");
}

void CMapBackgroundLayer::Init() {
    json jsonData = LoadJsonFromFile(TheGame::Instance().GetSource() + "BackGroundLayer.json");
    GRADIENT = jsonData["GRADIENT"];
    STATE_TIME = jsonData["STATE_TIME"];
    m_StateTimer = jsonData["STATE_TIMER"];
    TARGET_COLOR = {jsonData["TARGET_COLOR.R"], jsonData["TARGET_COLOR.G"], jsonData["TARGET_COLOR.B"],
                    jsonData["TARGET_COLOR.A"]};
    m_CurrColor = {jsonData["CURR_COLOR.R"],
                   jsonData["CURR_COLOR.G"],
                   jsonData["CURR_COLOR.B"], 255};
    if (m_CurrColor.r != 0 && m_CurrColor.g != 0 && m_CurrColor.b != 0)
        m_BackgroundState = BackgroundState::DAY;
    else
        m_BackgroundState = BackgroundState::NIGHT;
//    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), m_CurrColor.r, m_CurrColor.g, m_CurrColor.b,
//                           m_CurrColor.a);
}

json CMapBackgroundLayer::LoadJsonFromFile(const std::string &filePath) const {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    json jsonData;
    file >> jsonData;
    file.close();
    return jsonData;
}

void CMapBackgroundLayer::MapLayerRender() {
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), m_CurrColor.r, m_CurrColor.g, m_CurrColor.b,
                           m_CurrColor.a);
}
