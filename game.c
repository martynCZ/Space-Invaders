#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//Získání velikosti textu
void get_text_size(TTF_Font* font, const char* text, int* w, int* h){
  TTF_SizeText(font, text, w, h);
}

//Vypsání textu
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

//Bunkry
Bunker * init_bunkers(int bunker_count, int bunker_parts){
  Bunker* bunkers = malloc((bunker_count * bunker_parts)*sizeof(Bunker));

  int start_y = WINDOW_HEIGHT - 250;
  int bunker_width = 12;
  int bunker_height = 10;
  int bunker_size = 6;
  int gap = WINDOW_WIDTH / (bunker_count + 1);

  int pocet = 0;

  for(int i = 0; i < bunker_count; i++){
    int start_x = gap * (i + 1) - (bunker_width * bunker_size) / 2;
    for(int a = 0; a < bunker_height; a++){
      for(int b = 0; b < bunker_width; b++){
        if (a == 0 && (b == 0 || b == bunker_width - 1)) continue;
        if (a == 1 && (b == 0 || b == bunker_width - 1)) continue;
        if (a == 0 && (b == 1 || b == bunker_width - 2)) continue;
        if (a >= 6 && (b >= 4 && b <= 7)) continue;

        if(pocet < (bunker_parts * bunker_count)){
          bunkers[pocet].rect.x = start_x + b * bunker_size;
          bunkers[pocet].rect.y = start_y + a * bunker_size;
          bunkers[pocet].rect.w = bunker_size;
          bunkers[pocet].rect.h = bunker_size;
          bunkers[pocet].active = 1;
          pocet++;
        }
      }
    }
  }
  for (int y = pocet; y < (bunker_parts * bunker_count); y++){
    bunkers[y].active = 0;
  }
  return bunkers;
}

//Spodní čára
Line * init_lines(){
  int total_blocks = WINDOW_WIDTH / 10;
  Line* lines = malloc(total_blocks * sizeof(Line));

  int start_y =  WINDOW_HEIGHT - 50;
  int line_width = WINDOW_WIDTH;
  int block_size = 10;

  int pocet = 0;
  int start_x = 0;
  for(int i = 0; i < total_blocks; i++){   
        if(pocet < total_blocks){        
          lines[pocet].rect.x = start_x;
          lines[pocet].rect.y = start_y;
          lines[pocet].rect.w = block_size;
          lines[pocet].rect.h = block_size;
          lines[pocet].active = 1;
          pocet++;         
        }
        start_x += 10;
    }
  for (int y = pocet; y < total_blocks; y++){
    lines[y].active = 0;
  }
  return lines;
}
//Vytvoření enemies
Enemy* init_enemies(int lines) {
    Enemy* enemies = NULL;
    int enemy_width = 45;
    int enemy_height = 33;
    int enemy_count = 11;    
    int enemy_spacing = 18;
    
    enemies = malloc(enemy_count * lines * sizeof(Enemy));

    int enemy_total_width = enemy_count * enemy_width + (10) * enemy_spacing;
    int start_x = (WINDOW_WIDTH - enemy_total_width) / 2;
    int start_y = 80;

    for(int y = 0; y < lines; y++){
      for(int i = 0; i < enemy_count; i++){
        int index = y * enemy_count + i;
        
        // POZICE OBDELNÍKU
        enemies[index].rect = (SDL_Rect){ 
          .x = start_x  + i * (enemy_width + enemy_spacing),
          .y = WINDOW_HEIGHT/2 - start_y,
          .w = enemy_width,
          .h = enemy_height 
        };
        enemies[index].active = 1;
        enemies[index].explosion = 0;
        if (y == 0 || y == 1) {
            enemies[index].type = 1; 
            enemies[index].score_value = 10; 
        } else if (y == 2 || y == 3){
            enemies[index].type = 2;     
            enemies[index].score_value = 20;
        }
        else{
          enemies[index].type = 3;     
          enemies[index].score_value = 40;
        }
      }
      start_y += 45;
    }
    return enemies;
}

//Pohyb enemies
void enemy_move(Enemy* enemies, int * direction, int speed, int enemy_count) {
  int border_hit = 0;
  for(int i = 0; i < enemy_count; i++){
      if(enemies[i].active == 0){
        continue;
      }

      if(*direction == 1 && (enemies[i].rect.x >= WINDOW_WIDTH - enemies[i].rect.w))
      {
        border_hit = 1;
        break;
      }

      if(*direction == -1 && (enemies[i].rect.x <= 0)){
        border_hit = 1;
        break;
      }      
  }
  if(border_hit == 1){
        *direction = -(*direction);

        for(int j = 0; j < enemy_count; j++){
          enemies[j].rect.y += 20;
          enemies[j].rect.x += (*direction * speed);
        }
      }
      else{
        for(int i = 0; i < enemy_count; i++){
            enemies[i].rect.x += (*direction * speed);
        }
      }
}

//Pohyb hráče
void player_move(SDL_Rect* player_rect, const Uint8* key_state) {
    if (key_state[SDL_SCANCODE_LEFT] && player_rect->x > 0) {
      player_rect->x -= 5;
    }

    if (key_state[SDL_SCANCODE_RIGHT] && player_rect->x + player_rect->w < WINDOW_WIDTH) {
      player_rect->x += 5;
    }
}

//Konec hry
int win_game(Enemy * enemies, int enemy_count){ 
  for(int i = 0; i < enemy_count; i++){
    if(enemies[i].active == 1){
      return 0;
    }
  }
  return 1;
}

void run_game(SDL_Renderer* renderer, SDL_Window* window) {
    //Střelba
    int running = 1;
    int is_shooting = 0;
    int score = 0;
    SDL_Event event;
    //SHOT DELAY
    Uint32 last_shot_time = 0;
    const Uint32 shoot_delay = 500;

    //FONT
    TTF_Font* font = TTF_OpenFont("src/space-invaders.ttf", 34);

    //ENEMY TEXTURY
    SDL_Texture* enemy01 = IMG_LoadTexture(renderer, "src/enemy011.png");
    SDL_Texture* enemy02 = IMG_LoadTexture(renderer, "src/enemy01.png");
    SDL_Texture* enemy11 = IMG_LoadTexture(renderer, "src/enemy11.png");
    SDL_Texture* enemy12 = IMG_LoadTexture(renderer, "src/enemy12.png");
    SDL_Texture* enemy21 = IMG_LoadTexture(renderer, "src/enemy21.png");
    SDL_Texture* enemy22 = IMG_LoadTexture(renderer, "src/enemy22.png");
    SDL_Texture* enemy_hit = IMG_LoadTexture(renderer, "src/boom.png");
    SDL_Texture* enemy_shot = IMG_LoadTexture(renderer, "src/enemy_shot.png");
    
    //ENEMY SHOT
    

    int obrazek = 0;
    int total_enemies = 55;
    int direction = 1; //DOPRAVA x DOLEVA
    Enemy* enemies = init_enemies(5);

    //BUNKRY
    int bunkers_count = 4;
    int bunkers_parts = 150;
    int total_bunker_parts = bunkers_count * bunkers_parts;
    Bunker* bunkers = init_bunkers(bunkers_count, bunkers_parts);

    //BOTTOM LINE
    Line* lines = init_lines();

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
    int enemies_move_interval = 30;
    
    while (running) {
        Uint32 current_time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) running = 0;
          if (event.type == SDL_KEYDOWN){
              if (event.key.keysym.sym == SDLK_ESCAPE){
                 running = 0;
              }
              if (event.key.keysym.sym == SDLK_SPACE && !is_shooting && (current_time > last_shot_time + shoot_delay)) {
                  is_shooting = 1;
                  last_shot_time = current_time;
                  rect_shot.x = rect_player.x + rect_player.w / 2 - rect_shot.w / 2;
                  rect_shot.y = rect_player.y - rect_shot.h; 
              }
            }
        }
        const Uint8* key_state = SDL_GetKeyboardState(NULL);
        
        //PLAYER - MOVE
        player_move(&rect_player, key_state);

        //ENEMIES - MOVE
        program_cycle++;
        if(program_cycle >= enemies_move_interval){
          enemy_move(enemies, &direction, 10, total_enemies);
          obrazek = !obrazek;
          program_cycle = 0;
        }
        
        if (is_shooting) {
          rect_shot.y -= shot_speed;

        //ENEMY HIT CHECK
          for(int i = 0; i < total_enemies; i++) {
            if(enemies[i].active == 1 && SDL_HasIntersection(&rect_shot, &enemies[i].rect)){
              enemies[i].active = 2;  
              enemies[i].explosion = SDL_GetTicks(); 
              is_shooting = 0;                      
              score += enemies[i].score_value;
              break;
            }                    
        }
        //BUNKER HIT CHECK
        if(is_shooting){
          for(int i = total_bunker_parts - 1; i >= 0; i--) {
            if (bunkers[i].active && SDL_HasIntersection(&rect_shot, &bunkers[i].rect)) {
                bunkers[i].active = 0;
                is_shooting = 0;
                break;
            }
          }
        }
        //BOTTOM LINE HIT CHECK
        if(is_shooting){
          for(int i = 0; i < 50; i++) {
            if (lines[i].active && SDL_HasIntersection(&rect_shot, &lines[i].rect)) {
                lines[i].active = 0;
                is_shooting = 0;
                break;
            }
          }
        }
        //GAME END
        if(win_game(enemies, total_enemies) == 1){
          running = 0;             
          } 
        }

        if (rect_shot.y + rect_shot.h < 0) {
          is_shooting = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //BUNKERS
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for(int i = 0; i < total_bunker_parts; i++) {
          if (bunkers[i].active) {
              SDL_RenderFillRect(renderer, &bunkers[i].rect);
          }
        }

        //BOTTOM LINE
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for(int i = 0; i < (WINDOW_WIDTH / 10); i++) {
          if (lines[i].active) {
              SDL_RenderFillRect(renderer, &lines[i].rect );
          }
        }
        
        //ENEMIES
        for(int i = 0; i < total_enemies; i++) {
          if(enemies[i].active == 1) {
            SDL_Texture* currentTexture = NULL;
            if(enemies[i].type == 1){
              currentTexture = (obrazek == 0) ? enemy01 : enemy02;               
            }   
            else if(enemies[i].type == 2){
              currentTexture = (obrazek == 0) ? enemy11 : enemy12;
            }
            else{
              currentTexture = (obrazek == 0) ? enemy21 : enemy22;
            }
            SDL_RenderCopy(renderer, currentTexture, NULL, &enemies[i].rect);         
          }
          else if(enemies[i].active == 2){                          
            SDL_RenderCopy(renderer, enemy_hit, NULL, &enemies[i].rect);
            if(SDL_GetTicks() - enemies[i].explosion > 200){
              enemies[i].active = 0;
            }
          }
        }

        SDL_Color colorText = {255, 255, 255, 255};     
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 

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
    free(bunkers);
    SDL_DestroyTexture(enemy02);
    SDL_DestroyTexture(enemy01);
    SDL_DestroyTexture(enemy11);
    SDL_DestroyTexture(enemy12);
    SDL_DestroyTexture(enemy22);
    SDL_DestroyTexture(enemy21);
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(enemy_hit);
    TTF_CloseFont(font);
}