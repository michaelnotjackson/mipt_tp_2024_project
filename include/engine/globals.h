#pragma once

#include <chrono>
#include <random>
#include <mutex>

#include "entity.h"
#include "turn_controller.h"

enum class ActionType { FREE, BUSY };

class Room;

extern Room g_current_room;
extern std::vector<std::vector<int>> g_dungeon;
extern std::pair<int, int> g_current_room_coord;


extern IBaseEntity* g_current_executor;

extern CTurnController g_turnmanager;

extern ActionType g_current_action;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern const int g_move_speed;
extern bool g_move_in_process;
extern std::vector<PosType> g_current_path;

extern std::mt19937 g_rng;

extern std::mutex g_mutex;