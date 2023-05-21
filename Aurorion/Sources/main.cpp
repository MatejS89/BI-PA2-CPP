#include <iostream>
#include "CGame.h"


int main(int argc, char *args[]) {
    const int targetFps = 60;
    const float frameDelay = 1000.0F / targetFps;

    Uint32 frameTime = 0, frameStart = 0;

    if (!TheGame::Instance().Init("Aurorion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false))
        std::cout << "Initialization failed" << std::endl;
    while (TheGame::Instance().Running()) {
        frameStart = SDL_GetTicks64();
        TheGame::Instance().Update();
        TheGame::Instance().Render();
        frameTime = SDL_GetTicks64() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay((int) frameDelay - frameTime);
        }
    }
    TheGame::Instance().Clean();
    return 0;
}
