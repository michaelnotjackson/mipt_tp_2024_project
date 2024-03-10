#include <globals.h>
#include <utils.h>

#include <algorithm>
#include <set>
#include <vector>
#include <iostream>

PosType PosRoomToScreen(IBaseEntity* entity) {
  PosType map_pos = *entity->GetPos();

  CBaseAnimation anim = g_current_room.field[0][0]->GetTexture();

  PosType screen_pos;
  screen_pos.x =
      (static_cast<double>(map_pos.x) + 0.5) * (static_cast<double>(anim.frame.w) * anim.scale) -
      static_cast<double>(entity->animation.frame.w) * entity->animation.scale / 2;
  screen_pos.y =
      (static_cast<double>(map_pos.y) + 0.5) * (static_cast<double>(anim.frame.h) * anim.scale) -
      static_cast<double>(entity->animation.frame.h) * entity->animation.scale / 2;

  return screen_pos;
}

namespace FindPathSpace {
std::vector<std::vector<bool>> used;
std::vector<std::vector<int>> cost, eurest;
std::vector<std::vector<PosType>> parent;

std::vector<PosType>* RecursePath(PosType start, PosType end) {
  auto* ret = new std::vector<PosType>();

  while (end != start) {
    ret->push_back(end);
    end = parent[end.y][end.x];
  }

  std::reverse(ret->begin(), ret->end());

  std::cout << "=========================";

  return ret;
}
}  // namespace FindPathSpace

std::vector<PosType>* FindPath(PosType start, PosType end, const Room& room) {
  using namespace FindPathSpace;

  used.assign(room.field.size(),
              std::vector<bool>(room.field[0].size(), false));

  cost.assign(room.field.size(), std::vector<int>(room.field[0].size(), 1e9));
  cost[start.y][start.x] = 0;

  eurest.assign(room.field.size(), std::vector<int>(room.field[0].size(), 1e9));
  eurest[start.y][start.x] = std::max(std::abs(start.x - end.x), std::abs(start.y - end.y));

  parent.assign(room.field.size(),
                std::vector<PosType>(room.field[0].size(), {-1, -1}));

  auto cmp = [](const PosType& lhs, const PosType& rhs) -> bool {
    return eurest[lhs.y][lhs.x] < eurest[rhs.y][rhs.x];
  };

  std::set<PosType, decltype(cmp)> q(cmp);
  q.insert(start);

  int8_t dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
  int8_t dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

  while (!q.empty()) {
    PosType cur = *q.begin();
    q.erase(q.begin());

    if (cur == end) {
      return RecursePath(start, end);
    }

    used[cur.y][cur.x] = true;

    for (uint8_t i = 0; i < 8; ++i) {
      if (cur.x + dx[i] < 0 || cur.x + dx[i] >= room.field[0].size()) {
        continue;
      }
      if (cur.y + dy[i] < 0 || cur.y + dy[i] >= room.field.size()) {
        continue;
      }
      if (room.field[cur.y + dy[i]][cur.x + dx[i]]->GetObstacleType() == ObstacleType::WALL) {
        continue;
      }

      PosType vertex(cur.x + dx[i], cur.y + dy[i]);

      int score =
          cost[cur.y][cur.x] +
          static_cast<int>(room.field[vertex.y][vertex.x]->GetObstacleType());

      if (used[vertex.y][vertex.x] && score >= cost[vertex.y][vertex.x]) {
        continue;
      }
      if (!used[vertex.y][vertex.x] || score < cost[vertex.y][vertex.x]) {
        parent[vertex.y][vertex.x] = cur;
        cost[vertex.y][vertex.x] = score;
        eurest[vertex.y][vertex.x] =
            score +
            std::max(std::abs(vertex.x - end.x), std::abs(vertex.y - end.y));

        q.insert(vertex);
      }
      for (auto &v: q) {
        std::cout << "{" << v.x << ", " << v.y << ", " << eurest[v.y][v.x] << "} ";
      }
      std::cout << '\n';
    }
  }

  std::cout << "=========================\n";

  return nullptr;
}