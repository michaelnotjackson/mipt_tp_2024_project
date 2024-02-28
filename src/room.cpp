#include <SDL.h>
#include <interface/renderer.h>
#include <room.h>
#include <types.h>

#include <random>
#include <utility>
#include <vector>

int Room::GetWidth() { return this->width; }

int Room::GetHeight() { return this->height; }

FieldType& Room::GetField() { return this->field; }

CTile::CTile(CBaseAnimation texture)
    : animation(texture), flags(TileFlagsType::VISIBLE){};

CTile::CTile() : animation(), flags(TileFlagsType::VISIBLE) {}

Room::Room(int width, int height, FieldType field)

    : width(width), height(height), field(std::move(field)) {}

Room::Room(int width, int height)
    : width(width),
      height(height),
      field(width / 40, std::vector<CTile>(height / 40)) {}

CBaseAnimation CTile::GetTexture() { return this->animation; }

void Room::SetField(SDL_Texture* texture) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 1);
  SDL_Rect frame;
  frame.x = 40;
  frame.y = 40;
  frame.w = 40;
  frame.h = 40;
  CBaseAnimation grass_g(texture, frame, 1, SDL_GetTicks64(), 100);
  CTile grass(grass_g);
  frame.x = 400;
  CBaseAnimation grass_w(texture, frame, 1, SDL_GetTicks64(), 100);
  CTile sand(grass_w);
  for (int i = 0; i <= 680; i += 40) {
    for (int j = 0; j <= 680; j += 40) {
      if (dist(gen) == 0) {
        field[i / 40][j / 40] = grass;
      } else {
        field[i / 40][j / 40] = sand;
      }
    }
  }
}

void Room::DrawField() {
  for (int i = 0; i <= 680; i += 40) {
    for (int j = 0; j <= 680; j += 40) {
      CBaseAnimation tmp = field[i / 40][j / 40].GetTexture();
      Blit(tmp, i, j);
    }
  }
}