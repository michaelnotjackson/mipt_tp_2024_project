#include <room.h>

#include <SDL.h>
#include <interface/renderer.h>
#include <cstdlib>
#include <utility>
#include <vector>

int Room::GetWidth() { return this->width; }

int Room::GetHeight() { return this->height; }

FieldType &Room::GetField() { return this->field; }

Room::Room(int width, int height, FieldType field)

    : width(width), height(height), field(std::move(field)) {}

Room::Room(int width, int height)
    : width(width), height(height), field_0(width / 40, std::vector<int> (height / 40)) {}

void Room::SetField() {
  std::srand(std::time(nullptr));
  for (int i = 0; i <= 680; i += 40) {
    for (int j = 0; j <= 680; j += 40) {
      field_0[i / 40][j / 40] = std::rand() % 2;
    }
  }
}

void Room::DrawField(SDL_Texture *texture) {
  SDL_Rect frame;
  frame.x = 40;
  frame.y = 40;
  frame.w = 40;
  frame.h = 40;
  CBaseAnimation grass_g(texture, frame, 0, 0);
  frame.x = 400;
  CBaseAnimation grass_w(texture, frame, 0, 0);
  for (int i = 0; i <= 680; i += 40) {
    for (int j = 0; j <= 680; j += 40) {
      if (field_0[i / 40][j / 40] == 0) {
        Blit(grass_g, i, j);
      } else {
        Blit(grass_w, i, j);
      }
    }
  }
}

