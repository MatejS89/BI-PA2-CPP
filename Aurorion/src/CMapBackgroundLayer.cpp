#include "CMapBackgroundLayer.h"

std::shared_ptr<TileMap> CMapBackgroundLayer::GetTileMap() {
    return nullptr;
}

void CMapBackgroundLayer::LayerUpdate() {
    if (m_StateTimer <= 0) {
//        SDL_Color m_CurrColor;
//        SDL_GetRenderDrawColor(TheGame::Instance().GetRenderer(), &m_CurrColor.r, &m_CurrColor.g, &m_CurrColor.b, &m_CurrColor.a);
        if (IsDay(m_CurrColor) || IsNight(m_CurrColor))
            NextState();
        switch (m_BackgroundState) {
            case BackgroundState::DAY:
                ChangeIntoDay(m_CurrColor);
                break;
            case BackgroundState::NIGHT:
                ChangeIntoNight(m_CurrColor);
                break;
            default:
                break;
        }
        m_StateTimer = STATE_TIME;
    } else {
        m_StateTimer -= TheTimer::Instance().GetDeltaTime();
    }
}

CMapBackgroundLayer::CMapBackgroundLayer()
//m_BackgroundState(BackgroundState::DAY), m_StateTimer(0) {
//    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), TARGET_COLOR.r, TARGET_COLOR.g, TARGET_COLOR.b,
//                           TARGET_COLOR.a);
{}

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
    Uint8 currR = m_CurrColor.r - floor(m_CurrColor.r / GRADIENT);
    Uint8 currG = m_CurrColor.g - floor(m_CurrColor.g / GRADIENT);
    Uint8 currB = m_CurrColor.b - floor(m_CurrColor.b / GRADIENT);
    m_CurrColor = {currR, currG, currB, m_CurrColor.a};
    GraduallyDecrease(m_CurrColor);
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), m_CurrColor.r, m_CurrColor.g, m_CurrColor.b,
                           m_CurrColor.a);
}

void CMapBackgroundLayer::ChangeIntoNight(SDL_Color &tmp) {
    Uint8 currR = m_CurrColor.r + floor(TARGET_COLOR.r / GRADIENT);
    Uint8 currG = m_CurrColor.g + floor(TARGET_COLOR.g / GRADIENT);
    Uint8 currB = m_CurrColor.b + floor(TARGET_COLOR.b / GRADIENT);
    m_CurrColor = {currR, currG, currB, m_CurrColor.a};
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), m_CurrColor.r, m_CurrColor.g, m_CurrColor.b,
                           m_CurrColor.a);
}

bool CMapBackgroundLayer::IsNight(const SDL_Color &tmp) {
    return (m_CurrColor.r <= 30 && m_CurrColor.b <= 30 &&
            m_CurrColor.g <= 30);
}

bool CMapBackgroundLayer::IsDay(const SDL_Color &tmp) {
    return (m_CurrColor.r >= TARGET_COLOR.r &&
            m_CurrColor.g >= TARGET_COLOR.g &&
            m_CurrColor.b >= TARGET_COLOR.b);
}

void CMapBackgroundLayer::GraduallyDecrease(SDL_Color &tmp) {
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
//    jsonData["BACKGROUND_STATE"] = m_BackgroundState;
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
    SDL_SetRenderDrawColor(TheGame::Instance().GetRenderer(), m_CurrColor.r, m_CurrColor.g, m_CurrColor.b,
                           m_CurrColor.a);
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