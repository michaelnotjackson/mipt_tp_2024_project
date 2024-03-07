#include <globals.h>
#include <utils.h>

PosType PosRoomToScreen(IBaseEntity* entity) {
  PosType map_pos = *entity->GetPos();

  CBaseAnimation anim = g_current_room.field[0][0]->GetTexture();

  PosType screen_pos;
  screen_pos.x = map_pos.x * (anim.frame.w * anim.scale);
  screen_pos.y = map_pos.y * (anim.frame.h * anim.scale);

  return screen_pos;
}