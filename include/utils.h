#pragma once

#include <entity.h>
#include <room.h>
#include <globals.h>

PosType PosRoomToScreen(IBaseEntity* entity);

std::vector<PosType>* FindPath(PosType start, PosType end, const Room& room = g_current_room);