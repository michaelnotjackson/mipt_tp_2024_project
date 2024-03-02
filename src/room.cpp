#include <SDL.h>
#include <interface/renderer.h>
#include <room.h>
#include <types.h>
#include <assets_manager.h>
#include <globals.h>

#include <algorithm>
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
      field(width / 64, std::vector<CTile*>(height / 64)) {}

CBaseAnimation CTile::GetTexture() { return this->animation; }

void Room::SetField(SDL_Texture* texture) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 1);
  auto* grass = new CTile(assets_manager.GetAnimation("animations/terrain/grass"));
  auto* sand = new CTile((assets_manager.GetAnimation("animations/terrain/sand")));
  for (int i = 0; i < SCREEN_WIDTH; i += 64) {
    for (int j = 0; j < SCREEN_HEIGHT; j += 64) {
      if (dist(gen) == 0) {
        field[i / 64][j / 64] = grass;
      } else {
        field[i / 64][j / 64] = sand;
      }
    }
  }
}

PosType GetTilePos(CTile* tile, const Room& room) {
  int y = 0;
  int width = tile->GetTexture().frame.w * tile->GetTexture().scale;
  int height = tile->GetTexture().frame.h * tile->GetTexture().scale;
  for (auto& raw : room.field) {
    auto pos = std::find(raw.begin(), raw.end(), tile);
    if (pos != raw.end()) {
      return {static_cast<int>((pos - raw.begin()) * width), y * height};
    }
    ++y;
  }

  return {-1, -1};
}
