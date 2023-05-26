#include <iostream>
#include "CGame.h"
#include "CTimer.h"
#include "CMapParser.h"

#define TARGET_FPS 60

int main(int argc, char *args[]) {
    if (!TheGame::Instance().Init("Aurorion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false))
        std::cout << "Initialization failed" << std::endl;
    while (TheGame::Instance().Running()) {
        TheTimer::Instance().Tick();
        TheInputHandler::Instance().Listen();
        TheGame::Instance().Update();
        TheGame::Instance().Render();
        SDL_Delay(floor(1000 / TARGET_FPS - TheTimer::Instance().GetDeltaTime()));
    }
    TheGame::Instance().Clean();
    return 0;
}
