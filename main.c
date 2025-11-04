#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "game.h"

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

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  TTF_Font* font = TTF_OpenFont("src/space-invaders.ttf", 50);
  Uint32 startTime = SDL_GetTicks();

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
    int displayWidth = 0;
    int displayHeight = 0;
    int spacebar_w, spacebar_h, arrows_h, arrows_w;
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
              if (event.key.keysym.sym == SDLK_SPACE)
              {
               
              }
            }
        }
        SDL_RenderClear(renderer);
        int text_w, text_h;
        SDL_GetWindowSize(window, &displayWidth, &displayHeight);
        SDL_Color colorText = {255, 255, 255, 255};

        //TEXT - TITLE
        get_text_size(font, menu_text[0], &text_w, &text_h);        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     
        SDL_Rect rect_text_title = {
          .x = displayWidth/2 - text_w/2,
          .y = displayHeight/3 - text_h/2,
          .w = text_w,
          .h = text_h
        };        
        draw_text(renderer, font, colorText, rect_text_title, menu_text[0]);

        //TEXT - CONTROLS
        get_text_size(font, menu_text[1], &text_w, &text_h);
        SDL_Rect rect_text_controls = {
          .x = displayWidth/2 - text_w/2,
          .y = displayHeight/2.3 - text_h/2,
          .w = text_w,
          .h = text_h
        };       
        draw_text(renderer, font, colorText, rect_text_controls, menu_text[1]);

        /*TLAČÍTKA - OVLÁDÁNÍ*/
        
        //SPACEBAR
        SDL_Rect rect_spacebar = {
          .x = displayWidth/2 - spacebar_w,
          .y = displayHeight/1.8,
          .w = spacebar_w/1.7,
          .h = spacebar_h/1.7
        };    
        SDL_RenderCopy(renderer, spacebar, NULL, &rect_spacebar);

        //ARROWS

        SDL_Rect rect_arrows = {
          .x = displayWidth/1.06 - arrows_w,
          .y = displayHeight/1.6 - arrows_h/2,
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
          .x = displayWidth/2 - text_w/2,
          .y = displayHeight/1.3 - text_h/2,
          .w = text_w,
          .h = text_h
        };       
        draw_text(renderer, font, fadeColor, rect_text_continue, menu_text[2]);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return 0;
}