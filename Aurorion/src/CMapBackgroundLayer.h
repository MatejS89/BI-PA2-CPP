#pragma once

#include "CMapLayer.h"
#include "SDL2/SDL.h"
#include "CGame.h"
#include "CTimer.h"
#include <fstream>

using json = nlohmann::json;

/**
 * @brief Class representing a background layer for a map.
 * The `CMapBackgroundLayer` class is derived from the `CMapLayer` base class and provides functionality
 * for managing the background layer of a map. It supports transitioning between day and night states
 * by gradually changing the background color.
 */
class CMapBackgroundLayer : public CMapLayer {
public:
    CMapBackgroundLayer();

    /**
     * @brief Initializes the background layer.
     * This function initializes the background layer by setting up the initial state and color values
     * these values are loaded from BackGroundLayer.json file.
     */
    void Init();

    /**
     * @brief Updates the background layer.
     * This function is called to update the background layer, performing any necessary state transitions
     * and color changes based on the elapsed time.
     */
    void LayerUpdate() override;

    /**
     * @brief Saves the current state of the background in a BackGroundLayer.json file.
     */
    void SaveMapLayer() override;

private:
    /**
     * @enum BackgroundState
     * @brief Enumeration representing the possible background states.
     */
    enum class BackgroundState {
        DAY,
        NIGHT
    };

    /**
     * @brief Loads JSON data from a file.
     * @param filePath The path to the JSON file to load.
     * @return The loaded JSON data as a `json` object.
     */
    json LoadJsonFromFile(const std::string &filePath) const;

    /**
     * @brief Transitions to the next background state.
     * This function transitions the background layer to the next state (either day or night) based on
     * the current state.
     */
    void NextState();

    /**
     * @brief Changes the background into the day state.
     * This function changes the background layer into the day state, adjusting the color accordingly.
     */
    void ChangeIntoDay();

    /**
     * @brief Changes the background into the night state.
     * This function changes the background layer into the night state, adjusting the color accordingly.
     */
    void ChangeIntoNight();

    bool IsDay();

    bool IsNight();

    void GraduallyDecrease();

    BackgroundState m_BackgroundState;
    Uint8 GRADIENT = 100;
    float STATE_TIME = 50.0F;
    float m_StateTimer;
    SDL_Color m_CurrColor;
    SDL_Color TARGET_COLOR = {153, 204, 255, 255};
};
