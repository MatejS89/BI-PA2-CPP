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

    void SaveMapLayer() override;

private:

    void NextState();

    void ChangeIntoDay(SDL_Color &tmp);

    void ChangeIntoNight(SDL_Color &tmp);

    bool IsDay(const SDL_Color &tmp);

    bool IsNight(const SDL_Color &tmp);

    void GraduallyDecrease(SDL_Color &tmp);

    BackgroundState m_BackgroundState;
    const int GRADIENT = 50;
    const float STATE_TIME = 50.0F;
    float m_StateTimer;
    const SDL_Color TARGET_COLOR = {153, 204, 255, 255};
};
