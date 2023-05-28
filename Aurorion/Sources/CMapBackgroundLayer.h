#pragma once

#include "CMapLayer.h"
#include "SDL2/SDL.h"
#include "CGame.h"
#include "CTimer.h"

enum class BackgroundState {
    DAY,
    NIGHT
};

class CMapBackgroundLayer : public CMapLayer {
public:
    CMapBackgroundLayer();

    void LayerRender() override;

    void LayerUpdate() override;

    void NextState();

    std::shared_ptr<TileMap> GetTileMap() override;

    void ChangeIntoDay(SDL_Color &tmp);

    void ChangeIntoNight(SDL_Color &tmp);

    bool IsDay(const SDL_Color &tmp);

    bool IsNight(const SDL_Color &tmp);

    void GraduallyDecrease(SDL_Color &tmp);

private:
    BackgroundState m_BackgroundState;
    const int TRANSFORM = 50;
    const float STATE_TIME = 50.0F;
    float m_StateTimer;
    const SDL_Color TARGET_COLOR = {102, 153, 255, 255};
};
