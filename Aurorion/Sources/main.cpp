#include <iostream>
#include "game.h"

int main(int argc, char *args[]) {
    const int targetFps = 60;
    const int frameDelay = 1000 / targetFps;

    Uint64 frameStart;
    int frameTime;

    CGame *game = new CGame();
    game->init("Aurorion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while (game->running()) {
        frameStart = SDL_GetTicks64();
        game->handleEvents();
        game->update();
        game->render();
        frameTime = SDL_GetTicks64() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();
    return 0;
}
