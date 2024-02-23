#include <SDL.h>
#include <interface/init.h>
#include <interface/shared_vars.h>

#include <execution>
#include <string>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void InitSDL() {
  int rendererFlags, windowFlags;

  rendererFlags = SDL_RENDERER_ACCELERATED;

  windowFlags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::string msg = "Failed to initialize SDL: ";
    msg += SDL_GetError();

    throw std::runtime_error(msg);
  }

  app.window =
      SDL_CreateWindow("Test window", SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

  if (!app.window) {
    std::string msg = "Failed to open window: ";
    msg += SDL_GetError();
    throw std::runtime_error(msg);
  }

  app.renderer = SDL_CreateRenderer(app.window, SDL_GetWindowTitle(app.window),
                                    rendererFlags);

  if (!app.renderer) {
    std::string msg = "Failed to create renderer: ";
    msg += SDL_GetError();
    throw std::runtime_error(msg);
  }
}