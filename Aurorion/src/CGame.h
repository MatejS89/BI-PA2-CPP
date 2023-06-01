#pragma once

#include <iostream>
#include <string>
#include "CTextureManager.h"
#include "CVector2D.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "vector"
#include "CInputHandler.h"
#include "memory"
#include "CMap.h"
#include "CGameLayer.h"
#include <filesystem>

/**
 * @class CGame
 * @brief The main game class responsible for game initialization, update, rendering, and cleanup.
 */
class CGame {
public:
    /**
     * @brief Deleted copy constructor to prevent copying of CGame instances.
     */
    CGame(const CGame &other) = delete;

    static CGame &Instance();

    /**
     * @brief Initializes the game.
     * @param title The title of the game window.
     * @param xPos The x-coordinate of the game window's initial position.
     * @param yPos The y-coordinate of the game window's initial position.
     * @param width The width of the game window.
     * @param height The height of the game window.
     * @param fullScreen Whether to start the game in full-screen mode.
     * @return True if initialization is successful, false otherwise.
     */
    bool Init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen);

    /**
     * @brief Updates the game logic.
     */
    void Update();

    /**
     * @brief Renders the game.
     */
    void Render();

    /**
     * @brief Cleans up the game resources.
     */
    void Clean();

    /**
     * @brief Checks if the game is currently running.
     * @return True if the game is running, false otherwise.
     */
    bool IsRunning();

    /**
     * @brief Saves the game.
     */
    void Save();

    SDL_Renderer *GetRenderer();

    /**
     * @brief Quits the game.
     */
    void Quit();

    int GetWindowWidth() const;

    int GetWindowHeight() const;

    int GetMapWidth() const;

    int GetMapHeight() const;

    /**
     * @brief Loads the game from a source.
     * @param source Load directory name.
     */
    void LoadGame(const std::string &source);

    std::string GetSource() const;

    std::string GetNextSaveDir() const;

private:
    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    CGame();

    ~CGame();

    /**
     * @brief Parses the arguments.
     * @param args The arguments to parse.
     * @return Load directory name.
     */
    std::string parseArgs(const std::string &args);

    int getNextSaveNumber() const;

    static SDL_Renderer *m_renderer;

    static CGame m_instance;

    int m_height;

    int m_width;

    bool m_isRunning;

    static SDL_Window *m_window;

    std::string m_SourceSave;

    std::string m_NextSaveDir;

    std::vector<std::shared_ptr<CGameLayer>> m_GameLayers;
};

typedef CGame TheGame;
