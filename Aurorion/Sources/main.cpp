#include <iostream>
#include "CGame.h"

int main(int argc, char *args[]) {
    const int targetFps = 60;
    const int frameDelay = 1000 / targetFps;

    Uint64 frameStart;
    int frameTime;

    CGame *game = new CGame();
    if (!game->Init("Aurorion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false))
        std::cout << "Initialization failed" << std::endl;
    while (game->Running()) {
        frameStart = SDL_GetTicks64();
        game->HandleEvents();
        game->Update();
        game->Render();
        frameTime = SDL_GetTicks64() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->Clean();
    return 0;
}
