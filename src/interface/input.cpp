#include <SDL.h>
#include <interface/input.h>

#include <cstdlib>

void DoInput() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        exit(0);
        break;
      default:
        break;
    }
  }
}