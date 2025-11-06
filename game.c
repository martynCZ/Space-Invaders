#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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

SDL_Rect* draw_enemy(SDL_Renderer* renderer, SDL_Texture* enemy, int lines) {
    SDL_Rect rect_text_enemy;

    SDL_Rect* rect_enemies = NULL;
    int enemy_width = 45;
    int enemy_height = 33;
    int enemy_count = 11;    
    int enemy_spacing = 12;
    rect_enemies = malloc(enemy_count * lines * sizeof(SDL_Rect));

    int enemy_total_width = enemy_count * enemy_width + (10) * enemy_spacing;

    int start_x = (WINDOW_WIDTH - enemy_total_width) / 2;
      
    int start_y = 80;
    for(int y = 0; y < lines; y++){
      for(int i = 0; i < enemy_count; i++){
        rect_text_enemy = (SDL_Rect){ 
          .x = start_x  + i * (enemy_width + enemy_spacing),
          .y = WINDOW_HEIGHT/2 - start_y,
          .w = enemy_width,
          .h = enemy_height 
        };
        rect_enemies[y * enemy_count + i] = rect_text_enemy;               
      }
      start_y += 35;
    }
    return rect_enemies;
}

void player_move(SDL_Rect* player_rect, const Uint8* key_state) {
    if (key_state[SDL_SCANCODE_LEFT] && player_rect->x > 0) {
      player_rect->x -= 5;
    }

    if (key_state[SDL_SCANCODE_RIGHT] && player_rect->x + player_rect->w < WINDOW_WIDTH) {
      player_rect->x += 5;
    }

}
void run_game(SDL_Renderer* renderer, SDL_Window* window) {
  //PLAYER - SHOOTING
    int running = 1;
    int is_shooting = 0;
    int score = 0;

    SDL_Event event;
    //FONT
    TTF_Font* font = TTF_OpenFont("src/space-invaders.ttf", 34);
    //ENEMY - BOTTOM
    SDL_Texture* enemy011 = IMG_LoadTexture(renderer, "src/enemy011.png");
    SDL_Rect* enemies = draw_enemy(renderer, enemy011, 2);
      
    //DESTROYED ENEMIES
    SDL_Rect* destroyed_enemies = draw_enemy(renderer, enemy011, 0);
    destroyed_enemies = malloc(22 * sizeof(SDL_Rect));

    //PLAYER - SETTINGS
    int player_w, player_h;
    SDL_Texture* player = IMG_LoadTexture(renderer, "src/player.png");
    SDL_QueryTexture(player, NULL, NULL, &player_w, &player_h); 
    SDL_Rect rect_player = {
          .x = WINDOW_WIDTH/2 - player_w/2,
          .y = WINDOW_HEIGHT - 100,
          .w = 50,
          .h = 30
        };  
    int shot_speed = 10;
    SDL_Rect rect_shot = {
        .x = rect_player.x + rect_player.w / 2 - 5,
        .y = rect_player.y - 20,
        .w = 5,
        .h = 20
    };
    int program_cycle = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = 0;
        }
        const Uint8* key_state = SDL_GetKeyboardState(NULL);
        //PLAYER - MOVE
        player_move(&rect_player, key_state);

        //SHOT
        if (key_state[SDL_SCANCODE_SPACE] && !is_shooting) {
          is_shooting = 1;
          rect_shot.x = rect_player.x + rect_player.w / 2 - rect_shot.w / 2;
          rect_shot.y = rect_player.y - rect_shot.h;     
        }
        if (is_shooting) {
          rect_shot.y -= shot_speed;
          for(int i = 0; i < 22; i++) {
            if(SDL_HasIntersection(&rect_shot, &enemies[i]))
            {
              printf("ZNIČENA:\n x:%d y:%d", enemies[i].x, enemies[i].y);
              is_shooting = 0;
              destroyed_enemies[i] = enemies[i];
              enemies[i].x = -100;
              score += 10;
            } 
              }
          if (rect_shot.y + rect_shot.h < 0) {
            is_shooting = 0;
          }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //ENEMIES
        SDL_Color colorText = {255, 255, 255, 255};     
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        for(int i = 0; i < 22; i++) {
            SDL_RenderCopy(renderer, enemy011, NULL, &enemies[i]);
        }


        //TEXT - SCORE
        int text_w, text_h;
        colorText = (SDL_Color){255, 255, 255, 255};
        get_text_size(font, "Score", &text_w, &text_h);       
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     
        SDL_Rect rect_score_title = {
          .x = 15,
          .y = 15,
          .w = text_w,
          .h = text_h
        };
        char score_text[10];
        sprintf(score_text, "%04d", score);        
        draw_text(renderer, font, colorText, rect_score_title, "Score");
        SDL_Rect rect_text_number = {
          .x = 15,
          .y = 50,
          .w = text_w,
          .h = text_h 
        }; 
       draw_text(renderer, font, colorText, rect_text_number, score_text);
        //PLAYER      
        SDL_RenderCopy(renderer, player, NULL, &rect_player);

        if (is_shooting) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect_shot);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    free(enemies);
    free(destroyed_enemies);
    SDL_DestroyTexture(enemy011);
    SDL_DestroyTexture(player);
    TTF_CloseFont(font);
}