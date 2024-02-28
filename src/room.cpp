#include <SDL.h>
#include <interface/renderer.h>
#include <room.h>

#include <cstdlib>
#include <utility>

int Room::GetWidth() { return this->width; }

int Room::GetHeight() { return this->height; }

FieldType& Room::GetField() { return this->field; }

Room::Room(int width, int height, FieldType field)
    : width(width), height(height), field(std::move(field)) {}

Room::Room(int width, int height) : width(width), height(height) {}

void Room::SetField(SDL_Texture* texture) {
  std::srand(time(nullptr));
  SDL_Rect frame;
  frame.x = 40;
  frame.y = 40;
  frame.w = 40;
  frame.h = 40;
  CBaseAnimation grass_g(texture, frame, 0, SDL_GetTicks64(), 1);
  frame.x = 400;
  CBaseAnimation grass_w(texture, frame, 0, SDL_GetTicks64(), 1);
  for (int i = 0; i <= 680; i += 40) {
    for (int j = 0; j <= 680; j += 40) {
      int random = std::rand() % 2 + 0;
      if (random == 0) {
        Blit(grass_g, i, j);
      } else {
        Blit(grass_w, i, j);
      }
    }
  }
}
