#include <iostream>
#include "CGame.h"
#include "CTimer.h"
#include "CMapParser.h"

int main(int argc, char *args[]) {
    if (!TheGame::Instance().Init("Aurorion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false))
        std::cout << "Initialization failed" << std::endl;
    while (TheGame::Instance().Running()) {
        TheGame::Instance().Update();
        TheGame::Instance().Render();
        TheTimer::Instance().Tick();
    }
    TheGame::Instance().Clean();
    return 0;
}
