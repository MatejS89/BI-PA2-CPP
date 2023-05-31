#pragma once

#include "CMapLayer.h"
#include "SDL2/SDL.h"
#include "CGame.h"
#include "CTimer.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

enum class BackgroundState {
    DAY,
    NIGHT
};

class CMapBackgroundLayer : public CMapLayer {
public:
    CMapBackgroundLayer();

    void LayerUpdate() override;

    std::shared_ptr<TileMap> GetTileMap() override;

    void Init();

    void SaveMapLayer() override;

private:

    json LoadJsonFromFile(const std::string &filePath) const;

    void NextState();

    void ChangeIntoDay(SDL_Color &tmp);

    void ChangeIntoNight(SDL_Color &tmp);

    bool IsDay(const SDL_Color &tmp);

    bool IsNight(const SDL_Color &tmp);

    void GraduallyDecrease(SDL_Color &tmp);

    BackgroundState m_BackgroundState;
    Uint8 GRADIENT = 100;
    float STATE_TIME = 50.0F;
    float m_StateTimer;
    SDL_Color m_CurrColor;
    SDL_Color TARGET_COLOR = {153, 204, 255, 255};
};
