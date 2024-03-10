#pragma once

#include <room.h>
#include <entity.h>
#include <turnmanager.h>

extern Room g_current_room;

extern IBaseEntity* g_current_executor;

extern CTurnManager g_turnmanager;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern const int g_move_speed;
extern bool g_move_in_process;