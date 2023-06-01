#include "CGame.h"
#include "CMapParser.h"
#include "CTimer.h"
#include "CCamera.h"
#include "CHudLayer.h"
#include "CGameplayLayer.h"

SDL_Window *CGame::m_window = nullptr;

SDL_Renderer *CGame::m_renderer = nullptr;

CGame::CGame() {}

CGame::~CGame() {}

CGame CGame::m_instance;

CGame &CGame::Instance() {
    return m_instance;
}

bool CGame::Init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen) {
    int fullscreenFlag = 0;
    if (fullScreen)
        fullscreenFlag = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cout << "Initialized" << std::endl;
        m_window = SDL_CreateWindow(title, xPos, yPos, width, height, fullscreenFlag);
        if (m_window)
            std::cout << "Window created." << std::endl;
        else
            return false;

        m_renderer = SDL_CreateRenderer(m_window, -1, 0);
        if (m_renderer) {
            std::cout << "Renderer created." << std::endl;
        } else
            return false;
        m_SourceSave = "examples/NewGame/";
        m_isRunning = true;
        m_height = height;
        m_width = width;
    } else {
        m_isRunning = false;
        return false;
    }
    return true;
}

void CGame::Update() {
    for (const auto &item: m_GameLayers) {
        item->UpdateLayer();
    }
    CCamera::Instance().Update();
}

void CGame::Render() {
    SDL_RenderClear(m_renderer);
    for (const auto &item: m_GameLayers) {
        item->DrawLayer();
    }
    SDL_RenderPresent(m_renderer);
}

void CGame::Clean() {
    TheTextureManager::Instance().Clean();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    std::cout << "Game quit and cleaned" << std::endl;
}

bool CGame::IsRunning() {
    return m_isRunning;
}

SDL_Renderer *CGame::GetRenderer() {
    return m_renderer;
}

void CGame::Quit() {
    m_isRunning = false;
}

int CGame::GetWindowHeight() const {
    return m_height;
}

int CGame::GetWindowWidth() const {
    return m_width;
}

int CGame::GetMapWidth() const {
    return m_GameLayers.front()->GetMap()->GetMapWidth();
}

int CGame::GetMapHeight() const {
    return m_GameLayers.front()->GetMap()->GetMapHeight();
}

void CGame::Save() {
    if (std::filesystem::create_directory(m_NextSaveDir)) {
        std::cout << "Save Folder Created" << std::endl;
    } else
        std::cout << "Save Folder Failed" << std::endl;
    for (const auto &gameLayer: m_GameLayers) {
        gameLayer->SaveLayer();
    }
}

void CGame::LoadGame(const std::string &args) {
    m_SourceSave = parseArgs(args);
    if (!TheMapParser::Instance().Load()) {
        std::cout << "FAILED LOAD" << std::endl;
    }
    TheObjectFactory::Instance().RegisterObjects();
    std::shared_ptr<CHudLayer> hud = std::make_shared<CHudLayer>();
    std::shared_ptr<CGameplayLayer> gameplayLayer = std::make_shared<CGameplayLayer>();
    gameplayLayer->Init(hud);
    m_GameLayers.push_back(gameplayLayer);
    m_GameLayers.push_back(hud);
}

std::string CGame::GetSource() const {
    return m_SourceSave;
}

int CGame::getNextSaveNumber() const {
    int nextSaveNum = 1;
    for (const auto &saveGame: std::filesystem::directory_iterator("examples")) {
        if (saveGame.is_directory()) {
            std::string folderName = saveGame.path().filename().string();
            if (folderName.find("SaveGame") == 0) {
                std::string numString = folderName.substr(8);
                int saveNumber = std::stoi(numString);
                if (saveNumber >= nextSaveNum)
                    nextSaveNum = saveNumber + 1;
            }
        }
    }
    return nextSaveNum;
}

std::string CGame::GetNextSaveDir() const {
    return m_NextSaveDir;
}

std::string CGame::parseArgs(const std::string &args) {
    if (args.length() == 3 && args == "new") {
        m_NextSaveDir = "examples/SaveGame" + std::to_string(getNextSaveNumber()) + "/";
        return "examples/NewGame/";
    }
    if (args.length() == 6 && args.substr(0, 4) == "load") {
        std::stringstream ss(args);
        std::vector<std::string> parsed;
        std::string part;
        while (getline(ss, part, '-')) {
            parsed.push_back(part);
        }
        if (parsed.size() != 2) {
            return "ZLE";
        }
        m_NextSaveDir = "examples/SaveGame" + parsed.back() + "/";
        std::cout << m_NextSaveDir << std::endl;
        return "examples/SaveGame" + parsed.back() + "/";
    }
}
