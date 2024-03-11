#include <globals.h>

Room g_current_room;

IBaseEntity *g_current_executor;
CTurnManager g_turnmanager;

ActionType g_current_action;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 640;

const int g_move_speed = 200;
bool g_move_in_process = false;
std::vector<PosType> g_current_path;