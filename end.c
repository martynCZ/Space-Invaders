#include "end.h"
#include "game.h"
#include <stdio.h>

void render_centered_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = (WINDOW_WIDTH - rect.w) / 2;
    rect.y = y;

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

int end_screen(SDL_Renderer* renderer, int score, int won) {
    int running = 1;
    int action = 0;
    SDL_Event event;

    TTF_Font* font_big = TTF_OpenFont("src/space-invaders.ttf", 64);
    TTF_Font* font_small = TTF_OpenFont("src/space-invaders.ttf", 32);

    if (!font_big || !font_small) {
        printf("Chyba nacitani fontu: %s\n", TTF_GetError());
        return 0;
    }

    SDL_Color color_win = {0, 255, 0, 255};
    SDL_Color color_lose = {255, 0, 0, 255};
    SDL_Color color_white = {255, 255, 255, 255};

    char score_text[30];
    sprintf(score_text, "Final Score: %d", score);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                action = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                    action = 0;
                }
                if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN) {
                    running = 0;
                    action = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (won) {
            render_centered_text(renderer, font_big, "YOU WIN!", WINDOW_HEIGHT / 3, color_win);
        } else {
            render_centered_text(renderer, font_big, "GAME OVER", WINDOW_HEIGHT / 3, color_lose);
        }

        render_centered_text(renderer, font_small, score_text, WINDOW_HEIGHT / 2, color_white);
        render_centered_text(renderer, font_small, "Press ENTER to Restart", WINDOW_HEIGHT - 150, color_white);
        render_centered_text(renderer, font_small, "Press ESC to Quit", WINDOW_HEIGHT - 100, color_white);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font_big);
    TTF_CloseFont(font_small);

    return action;
}