#include <iostream>
#include <SDL.h>
#include "game.h"

int main(int argc, char *args[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Aurorion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 0, 150, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
