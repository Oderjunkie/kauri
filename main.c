#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "settings.h"
#define SDL_ERROR_REPORT(name) \
  fprintf(stderr, #name " failed: %s\n", SDL_GetError()), \
	exit(EXIT_FAILURE)

#define WINDOW_SETTINGS \
  "", \
  SDL_WINDOWPOS_UNDEFINED, \
  SDL_WINDOWPOS_UNDEFINED, \
  SCREEN_WIDTH, \
  SCREEN_HEIGHT, \
  0

#define RENDERER_SETTINGS \
  -1, \
  0

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
		SDL_ERROR_REPORT(SDL_Init);
  
  atexit(SDL_Quit);
  
  if (!(window = SDL_CreateWindow(WINDOW_SETTINGS)))
		SDL_ERROR_REPORT(SDL_CreateWindow);
  
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
  
  if (!(renderer = SDL_CreateRenderer(window, RENDERER_SETTINGS)))
		SDL_ERROR_REPORT(SDL_CreateRenderer);
  
  SDL_SetRenderDrawColor(renderer, COLOR_BG, 255);
	SDL_RenderClear(renderer);
  
  SDL_RenderPresent(renderer);
  for (;;) {
    static SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          return EXIT_SUCCESS;
          break;
        default:
          break;
      }
    }
    SDL_Delay(16);
  }
}
