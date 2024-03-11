#pragma once

#include <room.h>
#include <entity.h>
#include <turnmanager.h>

enum class ActionType {
  MOVE,
  ATTACK,
  CAST,
  WAIT
};

extern Room g_current_room;

extern IBaseEntity* g_current_executor;

extern CTurnManager g_turnmanager;

extern ActionType g_current_action;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern const int g_move_speed;
extern bool g_move_in_process;
extern std::vector<PosType> g_current_path;