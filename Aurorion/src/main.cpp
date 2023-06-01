#include <iostream>
#include "CGame.h"
#include "CTimer.h"

int main(int argc, char *args[]) {
    if (argc > 2)
        return 1;
    if (!TheGame::Instance().Init("Aurorion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false))
        std::cout << "Initialization failed" << std::endl;
    try {
        TheGame::Instance().LoadGame(args, argc);
    }
    catch (const std::exception &e) {
        std::cout << "Loading failed: " << e.what() << std::endl;
        return 1;
    }
    while (TheGame::Instance().IsRunning()) {
        TheTimer::Instance().Tick();
        TheInputHandler::Instance().Listen();
        TheGame::Instance().Update();
        TheGame::Instance().Render();
        SDL_Delay(1000 / TheTimer::Instance().GetTargetFps() - TheTimer::Instance().GetDeltaTime());
    }
    TheGame::Instance().Clean();
    return 0;
}
