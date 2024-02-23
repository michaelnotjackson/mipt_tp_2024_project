#include <SDL.h>
#include <interface/interface.h>

int main(int argc, char* argv[]) {
  InitSDL();

  while (true) {
    PrepareScene();

    DoInput();

    PresentScene();

    SDL_Delay(16);
  }

  return 0;
}