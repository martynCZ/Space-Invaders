#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

void init_game();
void update_game(float deltaTime);
void render_game(SDL_Renderer* renderer);
void free_game();
void play_game(SDL_Renderer* renderer);

#endif
