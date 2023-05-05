#include <iostream>
#include <SDL.h>
#include "game.h"

int main(int argc, char *args[]) {

    Game *game = new Game();
    game->init("Aurorion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}
