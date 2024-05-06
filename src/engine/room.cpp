#include "include/engine/room.h"

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#include "include/engine/assets_storage.h"

int Room::GetWidth() { return this->width; }

int Room::GetHeight() { return this->height; }

const FieldType &Room::GetField() const { return this->field; }

CTile::CTile(CBaseAnimation texture, ObstacleType obstacle_type)
    : animation(texture), obstacle_type(obstacle_type), entity_on(nullptr) {};

CTile::CTile() : animation(), obstacle_type(ObstacleType::NO_OBSTACLES), entity_on(nullptr) {}

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

void Room::SetField(int number) {
  using json = nlohmann::json;
  std::ifstream in("rooms/room.json");
  json file = json::parse(in);
  std::vector<std::vector<int>> numbers = file["room_" + std::to_string(number)]["room"];
  int tmp;
  auto grass = assets_manager.GetAnimation("animations/terrain/grass");
  auto sand = assets_manager.GetAnimation("animations/terrain/sand");
  auto wall = assets_manager.GetAnimation("animations/terrain/wall");
  int i = 0;
  for (const auto &row: numbers) {
    int j = 0;
    for (const auto &elem: row) {
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

void
AddRoomToDung(const std::string &s, std::queue<std::pair<int, int>> &border,
              int &number, int x, int y) {
  using json = nlohmann::json;
  std::ifstream in("rooms/room.json");
  json file = json::parse(in);
  std::vector<int> variants = file[s];
  int room_ind;
  {
    std::uniform_int_distribution<> find(0, variants.size() - 1);
    room_ind = find(g_rng);
  }
  g_dungeon[y][x] = variants[room_ind];
  border.push(std::pair(y, x));
  number--;
  if (number == 0) {
    CheckBorder();
  }
}

void CheckBorder() {
  using json = nlohmann::json;
  std::ifstream in("rooms/room.json");
  json file = json::parse(in);
  for (int i = 0; i < g_dungeon.size(); i++) {
    for (int j = 0; j < g_dungeon[i].size(); j++) {
      std::pair<int, int> curr = std::pair(j, i);
      if (g_dungeon[i][j] == 0) {
        continue;
      }
      std::string room = "room_" + std::to_string(g_dungeon[i][j]);

      std::vector<int> doors = file[room]["doors"];
      std::string s;
      s += std::to_string(doors[0]);
      s += std::to_string(doors[1]);
      s += std::to_string(doors[2]);
      s += std::to_string(doors[3]);
      if (doors[0] == 1) {
        if (i - 1 < 0 || g_dungeon[i - 1][j] == 0) {
          s[0] = '0';
        }
      }
      if (doors[1] == 1) {
        if (j + 1 >= g_dungeon[0].size() || g_dungeon[i][j + 1] == 0) {
          s[1] = '0';
        }
      }
      if (doors[2] == 1) {
        if (i + 1 >= g_dungeon.size() || g_dungeon[i + 1][j] == 0) {
          s[2] = '0';
        }
      }
      if (doors[3] == 1) {
        if (j - 1 < 0 || g_dungeon[i][j - 1] == 0) {
          s[3] = '0';
        }
      }
      g_dungeon[i][j] = file[s][0];
    }
  }
}

void CreateDung(std::vector<std::vector<int>> &dungeon) {
  using json = nlohmann::json;
  std::ifstream in("rooms/room.json");
  json file = json::parse(in);

  std::queue<std::pair<int, int>> border;
  border.push(std::pair(7, 7));

  {
    std::uniform_int_distribution<> distrib(1, 15);
    dungeon[7][7] = distrib(g_rng);
  }

  int number;

  {
    std::uniform_int_distribution<> distrib(10, 20);
    number = distrib(g_rng) - 1;
  }

  while (number > 0) {

    if (border.size() == 0) {
      CreateDung(dungeon);
      return;
    }

    std::pair curr = border.front();
    border.pop();

    std::string room = "room_" + std::to_string(dungeon[curr.first][curr.second]);

    std::vector<int> doors = file[room]["doors"];

    std::string s = "0000";

    int y = curr.first;
    int x = curr.second;

    //чекаем направление вверх
    if (doors[0] == 1 && y - 1 >= 0 && dungeon[y - 1][x] == 0) {

      s[2] = '1';

      y--;

      if (x - 1 >= 0 && dungeon[y][x - 1] != 0) {
        room = "room_" + std::to_string(dungeon[y][x - 1]);

        std::vector<int> d = file[room]["doors"];

        if (d[1] == 1) {
          s[3] = '1';
        }
      }

      if (x + 1 < dungeon[0].size() && dungeon[y][x + 1] != 0) {
        room = "room_" + std::to_string(dungeon[y][x + 1]);

        std::vector<int> d = file[room]["doors"];

        if (d[3] == 1) {
          s[1] = '1';
        }
      }

      if (y - 1 >= 0 && dungeon[y - 1][x] != 0) {
        room = "room_" + std::to_string(dungeon[y - 1][x]);

        std::vector<int> d = file[room]["doors"];

        if (d[2] == 1) {
          s[0] = '1';
        }
      }

      AddRoomToDung(s, border, number, x, y);
      if (number == 0) { return; }
      y++;
    }

    s = "0000";
    //чекаем направление вниз
    if (doors[2] == 1 && y + 1 < dungeon.size() && dungeon[y + 1][x] == 0) {

      s[0] = '1';
      y++;

      if (x - 1 >= 0 && dungeon[y][x - 1] != 0) {
        room = "room_" + std::to_string(dungeon[y][x - 1]);
        std::vector<int> d = file[room]["doors"];
        if (d[1] == 1) {
          s[3] = '1';
        }
      }

      if (x + 1 < dungeon[0].size() && dungeon[y][x + 1] != 0) {
        room = "room_" + std::to_string(dungeon[y][x + 1]);
        std::vector<int> d = file[room]["doors"];
        if (d[3] == 1) {
          s[1] = '1';
        }
      }

      if (y + 1 < dungeon.size() && dungeon[y + 1][x] != 0) {
        room = "room_" + std::to_string(dungeon[y + 1][x]);
        std::vector<int> d = file[room]["doors"];
        if (d[0] == 1) {
          s[2] = '1';
        }
      }

      AddRoomToDung(s, border, number, x, y);
      if (number == 0) { return; }
      y--;
    }

    s = "0000";
    //чекаем направление вправо
    if (doors[1] == 1 && x + 1 < dungeon[0].size() && dungeon[y][x + 1] == 0) {

      s[3] = '1';
      x++;

      if (y + 1 < dungeon.size() && dungeon[y + 1][x] != 0) {
        room = "room_" + std::to_string(dungeon[y + 1][x]);
        std::vector<int> d = file[room]["doors"];
        if (d[0] == 1) {
          s[2] = '1';
        }
      }

      if (x + 1 < dungeon[0].size() && dungeon[y][x + 1] != 0) {
        room = "room_" + std::to_string(dungeon[y][x + 1]);
        std::vector<int> d = file[room]["doors"];
        if (d[3] == 1) {
          s[1] = '1';
        }
      }

      if (y - 1 >= 0 && dungeon[y - 1][x] != 0) {
        room = "room_" + std::to_string(dungeon[y - 1][x]);
        std::vector<int> d = file[room]["doors"];
        if (d[2] == 1) {
          s[0] = '1';
        }
      }

      AddRoomToDung(s, border, number, x, y);
      if (number == 0) { return; }
      x--;
    }

    s = "0000";
    //чекаем направление влево
    if (doors[3] == 1 && x - 1 >= 0 && dungeon[y][x - 1] == 0) {

      s[1] = '1';
      x--;

      if (x - 1 >= 0 && dungeon[y][x - 1] != 0) {
        room = "room_" + std::to_string(dungeon[y][x - 1]);
        std::vector<int> d = file[room]["doors"];
        if (d[1] == 1) {
          s[3] = '1';
        }
      }

      if (y + 1 < dungeon.size() && dungeon[y + 1][x] != 0) {
        room = "room_" + std::to_string(dungeon[y + 1][x]);
        std::vector<int> d = file[room]["doors"];
        if (d[0] == 1) {
          s[2] = '1';
        }
      }

      if (y - 1 >= 0 && dungeon[y - 1][x] != 0) {
        room = "room_" + std::to_string(dungeon[y - 1][x]);
        std::vector<int> d = file[room]["doors"];
        if (d[2] == 1) {
          s[0] = '1';
        }
      }

      AddRoomToDung(s, border, number, x, y);
      if (number == 0) { return; }
      x++;
    }
  }
}
