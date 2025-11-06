#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

void run_game(SDL_Renderer* renderer, SDL_Window* window);
void draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text);
void get_text_size(TTF_Font* font, const char* text, int* w, int* h);

#endif
