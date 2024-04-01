#pragma once

#include "entity.h"
#include "globals.h"
#include "room.h"

PosType EntityPosRoomToScreen(IBaseEntity* entity);
SDL_Point PointRoomToScreenTileCenter(PosType room_point);

std::vector<PosType>* FindPath(PosType start, PosType end, const Room& room = g_current_room);