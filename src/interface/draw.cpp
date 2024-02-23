#include <interface/draw.h>
#include <SDL.h>
#include <interface/shared_vars.h>

void PrepareScene() {
  SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
  SDL_RenderClear(app.renderer);
}

void PresentScene() {
  SDL_RenderPresent(app.renderer);
}