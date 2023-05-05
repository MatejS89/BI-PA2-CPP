#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

#ifndef AURORION_GAME_H
#define AURORION_GAME_H

class Game {
public:
    Game();

    ~Game();

    void init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen);

    void handleEvents();

    void update();

    void render();

    void clean();

    bool running();

private:
    bool m_IsRunning;
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
    SDL_Texture *m_Player;
};

#endif //AURORION_GAME_H
