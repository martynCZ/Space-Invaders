#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
void get_text_size(TTF_Font* font, const char* text, int* w, int* h){
  TTF_SizeText(font, text, w, h);
}

void draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text)
{
  SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);  
    SDL_Rect actual_location = location; 
    actual_location.w = surface->w;
    actual_location.h = surface->h;
    SDL_SetTextureAlphaMod(texture, color.a);
    SDL_RenderCopy(renderer, texture, NULL, &actual_location);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void run_game(SDL_Renderer* renderer, SDL_Window* window) {
    int running = 1;
    SDL_Event event;
    TTF_Font* font = TTF_OpenFont("src/space-invaders.ttf", 34);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = 0;
        }
       
        SDL_RenderClear(renderer);
        
        //TEXT - TITLE
        int text_w, text_h;
        SDL_Color colorText = {255, 255, 255, 255};
        get_text_size(font, "Score", &text_w, &text_h);       
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     
        SDL_Rect rect_text_title = {
          .x = 15,
          .y = 15,
          .w = text_w,
          .h = text_h
        };        
        draw_text(renderer, font, colorText, rect_text_title, "Score");

        SDL_RenderPresent(renderer);
    }
}
