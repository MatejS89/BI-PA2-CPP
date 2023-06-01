#include "CGame.h"
#include "CMapParser.h"
#include "CTimer.h"
#include "CCamera.h"
#include "CHudLayer.h"
#include "CGameplayLayer.h"

SDL_Window *CGame::m_Window = nullptr;

SDL_Renderer *CGame::m_Renderer = nullptr;

CGame::CGame() {}

CGame::~CGame() {}

CGame CGame::m_Instance;

CGame &CGame::Instance() {
    return m_Instance;
}

bool CGame::Init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen) {
    int fullscreenFlag = 0;
    if (fullScreen)
        fullscreenFlag = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cout << "Initialized" << std::endl;
        m_Window = SDL_CreateWindow(title, xPos, yPos, width, height, fullscreenFlag);
        if (m_Window)
            std::cout << "Window created." << std::endl;
        else
            return false;

        m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
        if (m_Renderer) {
            std::cout << "Renderer created." << std::endl;
        } else
            return false;
        m_SourceSave = "examples/NewGame/";
        m_IsRunning = true;
        m_Height = height;
        m_Width = width;
    } else {
        m_IsRunning = false;
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
    SDL_RenderClear(m_Renderer);
    for (const auto &item: m_GameLayers) {
        item->DrawLayer();
    }
    SDL_RenderPresent(m_Renderer);
}

void CGame::Clean() {
    TheTextureManager::Instance().Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
    std::cout << "Game quit and cleaned" << std::endl;
}

bool CGame::IsRunning() {
    return m_IsRunning;
}

SDL_Renderer *CGame::GetRenderer() {
    return m_Renderer;
}

void CGame::Quit() {
    m_IsRunning = false;
}

int CGame::GetWindowHeight() const {
    return m_Height;
}

int CGame::GetWindowWidth() const {
    return m_Width;
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
    }
    for (const auto &gameLayer: m_GameLayers) {
        gameLayer->SaveLayer();
    }
}

void CGame::LoadGame(char *args[], const int argc) {
    ParseArgs(args, argc);
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

int CGame::GetNextSaveNumber() const {
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

void CGame::ParseArgs(char *args[], const int argc) {
    if (argc == 1) {
        NewGame();
        return;
    }
    std::string arg;
    if (argc == 2)
        arg = args[1];
    else
        throw std::logic_error("Invalid arguments.");

    if (arg == "new") {
        NewGame();
        return;
    }
    if (arg.length() >= 6 && arg.substr(0, 4) == "load") {
        std::stringstream ss(arg);
        std::vector<std::string> parsed;
        std::string part;
        while (getline(ss, part, '-')) {
            parsed.push_back(part);
        }
        if (parsed.size() != 2) {
            throw std::logic_error("Invalid arguments.");
        }
        m_NextSaveDir = "examples/SaveGame" + parsed.back() + "/";
        m_SourceSave = "examples/SaveGame" + parsed.back() + "/";
        CheckSourceSave();
        std::cout << "SaveFile loaded: " << m_SourceSave << std::endl;
        return;
    }
}

void CGame::NewGame() {
    m_SourceSave = "examples/NewGame/";
    m_NextSaveDir = "examples/SaveGame" + std::to_string(GetNextSaveNumber()) + "/";
}

void CGame::CheckSourceSave() {
    if (!(std::filesystem::exists(m_SourceSave) && std::filesystem::is_directory(m_SourceSave)))
        throw std::logic_error("Save directory doesnt exists!");
    if (!(std::filesystem::exists(m_SourceSave + "GameObjectData.json") &&
          std::filesystem::is_regular_file(m_SourceSave + "GameObjectData.json") &&
          std::filesystem::exists(m_SourceSave + "BackGroundLayer.json") &&
          std::filesystem::is_regular_file(m_SourceSave + "BackGroundLayer.json") &&
          std::filesystem::exists(m_SourceSave + "map.tmx") &&
          std::filesystem::is_regular_file(m_SourceSave + "map.tmx")))
        throw std::logic_error("Save directory corrupted");
}
