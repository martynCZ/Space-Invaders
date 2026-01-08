#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "game.h"
#include "end.h"


int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  //načtení fontu
  TTF_Font* font = TTF_OpenFont("src/space-invaders.ttf", 50);
  Uint32 startTime = SDL_GetTicks();

  //vytvoření okna
  SDL_Window* window = SDL_CreateWindow(
    "Space Invaders",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    1200,
    800,
    SDL_WINDOW_SHOWN 
);
  SDL_Renderer* renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  const char* menu_text[] = {
    "Space Invaders", 
    "Controls", 
    "Press Space to start..."
  };

  SDL_Event event;
    int running = 1;   
    int spacebar_w, spacebar_h, arrows_h, arrows_w;

    //načtení obrázků
    SDL_Texture* spacebar = IMG_LoadTexture(renderer, "src/spacebar.png");
    SDL_Texture* arrows = IMG_LoadTexture(renderer, "src/arrows.png");
    SDL_QueryTexture(spacebar, NULL, NULL, &spacebar_w, &spacebar_h);    
    SDL_QueryTexture(arrows, NULL, NULL, &arrows_w, &arrows_h); 
    
    while (running == 1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
              //START hry
              if (event.key.keysym.sym == SDLK_SPACE)
              {
              int playing = 1;
              while(playing == 1){
                playing = run_game(renderer, window);
              }
               startTime = SDL_GetTicks();
               SDL_RenderClear(renderer);
              }
            }
        }
        SDL_RenderClear(renderer);
        int text_w, text_h;
        SDL_Color colorText = {255, 255, 255, 255};

        //TEXT - nadpis
        get_text_size(font, menu_text[0], &text_w, &text_h);        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     
        SDL_Rect rect_text_title = {
          .x = WINDOW_WIDTH/2 - text_w/2,
          .y = WINDOW_HEIGHT/3 - text_h/2,
          .w = text_w,
          .h = text_h
        };        
        draw_text(renderer, font, colorText, rect_text_title, menu_text[0]);

        //TEXT - ovládání
        get_text_size(font, menu_text[1], &text_w, &text_h);
        SDL_Rect rect_text_controls = {
          .x = WINDOW_WIDTH/2 - text_w/2,
          .y = WINDOW_HEIGHT/2.3 - text_h/2,
          .w = text_w,
          .h = text_h
        };       
        draw_text(renderer, font, colorText, rect_text_controls, menu_text[1]);

        /*TLAČÍTKA - OVLÁDÁNÍ*/       
        //SPACEBAR
        SDL_Rect rect_spacebar = {
          .x = WINDOW_WIDTH/2 - spacebar_w,
          .y = WINDOW_HEIGHT/1.8,
          .w = spacebar_w/1.7,
          .h = spacebar_h/1.7
        };    
        SDL_RenderCopy(renderer, spacebar, NULL, &rect_spacebar);

        //ARROWS
        SDL_Rect rect_arrows = {
          .x = WINDOW_WIDTH/1.06 - arrows_w,
          .y = WINDOW_HEIGHT/1.6 - arrows_h/2,
          .w = arrows_w/1.7,
          .h = arrows_h/1.7
        };    
        SDL_RenderCopy(renderer, arrows, NULL, &rect_arrows);

        //TEXT - Press space...        
        Uint32 time = SDL_GetTicks() - startTime;
        float phase = (sin(time / 500.0f) + 1.0f) / 2.0f;
        Uint8 alpha = (Uint8)(phase * 255);
        SDL_Color fadeColor = {255, 255, 255, alpha};

        get_text_size(font, menu_text[2], &text_w, &text_h);
        SDL_Rect rect_text_continue = {
          .x = WINDOW_WIDTH/2 - text_w/2,
          .y = WINDOW_HEIGHT/1.3 - text_h/2,
          .w = text_w,
          .h = text_h
        };       
        draw_text(renderer, font, fadeColor, rect_text_continue, menu_text[2]);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(spacebar);
    SDL_DestroyTexture(arrows);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}