#include <SDL2/SDL.h>
#include "game.h"

int playerX, playerY;

void init_game()
{
    playerX = 600;
    playerY = 700;
}

void update_game(float deltaTime)
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_LEFT])
        playerX -= 300 * deltaTime;
    if (keystates[SDL_SCANCODE_RIGHT])
        playerX += 300 * deltaTime;
}

void render_game(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect playerRect = {playerX - 25, playerY - 25, 50, 50};
    SDL_RenderFillRect(renderer, &playerRect);

    SDL_RenderPresent(renderer);
}

void free_game()
{

}

void play_game(SDL_Renderer* renderer)
{
    int playing = 1;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (playing)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                playing = 0;
        }

        update_game(deltaTime);
        render_game(renderer);
    }

    free_game();
}