#include <assets_storage.h>
#include <globals.h>
#include <room.h>
#include <types.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <utility>
#include <vector>
#include <iostream>


int Room::GetWidth() { return this->width; }

int Room::GetHeight() { return this->height; }

const FieldType &Room::GetField() const { return this->field; }

CTile::CTile(CBaseAnimation texture, ObstacleType obstacle_type)
    : animation(texture), obstacle_type(obstacle_type) {};

CTile::CTile() : animation(), obstacle_type(ObstacleType::NO_OBSTACLES) {}

Room::Room(int width, int height, FieldType field)

    : width(width), height(height), field(std::move(field)) {};

void CTile::SetTexture(CBaseAnimation texture) {
  animation = texture;
}

void CTile::SetObstacleType(ObstacleType obstacle_type) {
  obstacle_type = obstacle_type;
}

ObstacleType CTile::GetObstacleType() { return obstacle_type; }


Room::Room(int width, int height)
    : width(width),
      height(height),
      field(width / 64, std::vector<CTile *>(height / 64)) {
}

CBaseAnimation CTile::GetTexture() const { return this->animation; }

void Room::SetField() {
  using json = nlohmann::json;
  std::ifstream in("rooms/room.json");
  json file = json::parse(in);
  std::vector<std::vector<int>> numbers = file["numbers"];
  int tmp;
  auto grass = assets_manager.GetAnimation("animations/terrain/grass");
  auto sand = assets_manager.GetAnimation("animations/terrain/sand");
  auto wall = assets_manager.GetAnimation("animations/terrain/wall");
  int i = 0;
  for (const auto& row : numbers) {
    int j = 0;
      for (const auto& elem : row) {
          tmp = static_cast<int>(elem);
          if (tmp == 1) {
            field[i][j] = new CTile(grass, ObstacleType::NO_OBSTACLES);
          } else if (tmp == 2) {
            field[i][j] = new CTile(sand, ObstacleType::NO_OBSTACLES);
          } else {
            field[i][j] = new CTile(wall, ObstacleType::WALL);
          }
        j++;
      }
      i++;
  }
}

PosType GetTilePos(const CTile *tile, const Room &room) {
  int y = 0;
  for (auto &raw: room.field) {
    auto pos = std::find(raw.begin(), raw.end(), tile);
    if (pos != raw.end()) {
      return {static_cast<int>(pos - raw.begin()), y};
    }
    ++y;
  }

  return {-1, -1};
}
