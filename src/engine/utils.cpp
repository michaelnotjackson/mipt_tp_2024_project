#include "include/engine/utils.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "include/engine/event_storage.h"
#include "include/engine/mouse_eventlisteners.h"

PosType EntityPosRoomToScreen(IBaseEntity* entity) {
  PosType map_pos = *entity->GetPos();

  CBaseAnimation anim = g_current_room.field[0][0]->GetTexture();

  PosType screen_pos;
  screen_pos.x = (static_cast<double>(map_pos.x) + 0.5) *
                     (static_cast<double>(anim.frame.w) * anim.scale) -
                 static_cast<double>(entity->animation.frame.w) *
                     entity->animation.scale / 2;
  screen_pos.y = (static_cast<double>(map_pos.y) + 0.5) *
                     (static_cast<double>(anim.frame.h) * anim.scale) -
                 static_cast<double>(entity->animation.frame.h) *
                     entity->animation.scale / 2;

  return screen_pos;
}

SDL_Point PointRoomToScreenTileCenter(PosType room_point) {
  SDL_Point screen_point;

  screen_point.x =
      g_current_room.field[0][0]->GetTexture().frame.w * room_point.x +
      g_current_room.field[0][0]->GetTexture().frame.w / 2;
  screen_point.y =
      g_current_room.field[0][0]->GetTexture().frame.h * room_point.y +
      g_current_room.field[0][0]->GetTexture().frame.h / 2;

  return screen_point;
}

namespace FindPathSpace {
std::vector<std::vector<bool>> used, in_queue;
std::vector<std::vector<int64_t>> cost;
std::vector<std::vector<PosType>> parent;

std::vector<PosType>* RecursePath(PosType start, PosType end, bool f) {
  auto* ret = new std::vector<PosType>();

  while (end != start) {
    ret->push_back(end);
    end = parent[end.y][end.x];
  }

  std::reverse(ret->begin(), ret->end());

  if (f) {
    ret->pop_back();
  }

  return ret;
}

class Cmp {
 public:
  bool operator()(const std::pair<PosType, int>& lhs,
                  const std::pair<PosType, int>& rhs) {
    return lhs.second > rhs.second;
  }
};

int calc_heurest(const PosType& from, const PosType& to) {
  return std::max(std::abs(from.x - to.x), std::abs(from.y - to.y)) * 5;
}
}  // namespace FindPathSpace

std::vector<PosType>* FindPath(PosType start, PosType end, const Room& room) {
  if (start == end) {
    return nullptr;
  }
  if (room.field[end.y][end.x]->GetObstacleType() == ObstacleType::WALL) {
    return nullptr;
  }

  using namespace FindPathSpace;

  used.assign(room.field.size(),
              std::vector<bool>(room.field[0].size(), false));

  in_queue.assign(room.field.size(),
                  std::vector<bool>(room.field[0].size(), false));
  in_queue[start.y][start.x] = true;

  cost.assign(room.field.size(),
              std::vector<int64_t>(room.field[0].size(), 1e10));
  cost[start.y][start.x] = 0;

  parent.assign(room.field.size(),
                std::vector<PosType>(room.field[0].size(), {-1, -1}));

  std::priority_queue<std::pair<PosType, int64_t>,
                      std::vector<std::pair<PosType, int64_t>>, Cmp>
      q;

  q.emplace(start, calc_heurest(start, end));

  int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
  int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

  while (!q.empty()) {
    PosType current = q.top().first;
    q.pop();

    in_queue[current.y][current.x] = false;
    used[current.y][current.x] = true;

    if (current == end) {
      bool f = false;
      if (room.field[end.y][end.x]->entity_on != nullptr) {
        f = true;
      }
      return RecursePath(start, end, f);
    }

    for (int i = 0; i < 8; ++i) {
      PosType next(current.x + dx[i], current.y + dy[i]);

      if (next.x < 0 || next.x >= g_current_room.field[0].size() ||
          next.y < 0 || next.y >= g_current_room.field.size()) {
        continue;
      }
      if (used[next.y][next.x]) {
        continue;
      }

      int obstacle_cost =
          static_cast<int>(
              g_current_room.field[next.y][next.x]->GetObstacleType());

      if (g_current_room.field[next.y][next.x]->entity_on != nullptr &&
          (next.x != end.x || next.y != end.y)) {
        if (std::abs(next.x - end.x) <= 1 && std::abs(next.y - end.y) <= 1) {
          obstacle_cost =
              std::max(obstacle_cost, static_cast<int>(ObstacleType::WALL));
        } else {
          obstacle_cost = std::max(
              obstacle_cost, static_cast<int>(ObstacleType::HALF_SPEED));
        }
      }

      int64_t new_cost = cost[current.y][current.x] + obstacle_cost +
                         (dx[i] != 0 && dy[i] != 0);

      if (new_cost >= cost[next.y][
                          next.x]) {
        continue;
      }

      int64_t priority = new_cost + calc_heurest(next, end);
      cost[next.y][next.x] = new_cost;
      parent[next.y][next.x] = current;

      if (!in_queue[next.y][next.x]) {
        q.emplace(next, priority);
        in_queue[next.y][next.x] = true;
      }
    }
  }

  return nullptr;
}
void RecalculatePath() {
  std::vector<PosType>* tmp_path = FindPath(
      *g_current_executor->GetPos(),
      GetTilePos(event_manager.current_hover->GetTile(), g_current_room));
  if (tmp_path == nullptr || tmp_path->size() == 0) {
    g_current_path.clear();
  } else {
    g_current_path.assign(tmp_path->begin(), tmp_path->end());
  }
}