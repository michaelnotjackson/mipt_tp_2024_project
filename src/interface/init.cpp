#include <SDL.h>
#include <interface/init.h>
#include <interface/shared_vars.h>

#include <execution>
#include <string>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

AppClass app;

void InitSDL() {
  int rendererFlags, windowFlags;

  rendererFlags = SDL_RENDERER_ACCELERATED;

  windowFlags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::string msg = "Failed to initialize SDL: ";
    msg += SDL_GetError();

    throw std::runtime_error(msg);
  }

  app.window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, windowFlags);

  if (!app.window) {
    std::string msg = "Failed to open window: ";
    msg += SDL_GetError();
    throw std::runtime_error(msg);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

  if (!app.renderer) {
    std::string msg = "Failed to create renderer: ";
    msg += SDL_GetError();
    throw std::runtime_error(msg);
  }
}