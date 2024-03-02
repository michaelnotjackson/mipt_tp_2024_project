#include <SDL.h>
#include <interface/renderer.h>
#include <room.h>
#include <types.h>
#include <assets_manager.h>

#include <random>
#include <utility>
#include <vector>

int Room::GetWidth() { return this->width; }

int Room::GetHeight() { return this->height; }

const FieldType& Room::GetField() const { return this->field; }

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
  CTile grass(assets_manager.GetAnimation("animations/terrain/grass"));
  CTile sand(assets_manager.GetAnimation("animations/terrain/grass"));
  for (int i = 0; i <= SCREEN_WIDTH; i += 64) {
    for (int j = 0; j <= SCREEN_HEIGHT; j += 64) {
      if (dist(gen) == 0) {
        field[i / 64][j / 64] = grass;
      } else {
        field[i / 64][j / 64] = sand;
      }
    }
  }
}