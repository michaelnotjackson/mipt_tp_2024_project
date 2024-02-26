#include <entity.h>

CBaseEntity::CBaseEntity(int hp,
                         PosType pos,
                         SizeType size,
                         SDL_Texture *texture,
                         ObstacleType obstacle_degree)
    : hp(hp),
      pos(pos),
      size(size),
      texture(texture),
      obstacle_degree(obstacle_degree){}

CBaseEntity::CBaseEntity()
    : hp(0),
      pos(0, 0),
      size(SizeType::MEDIUM),
      texture(nullptr),
      obstacle_degree(ObstacleType::HALF_SPEED) {}

int CBaseEntity::GetHp() { return this->hp; }

PosType CBaseEntity::GetPos() { return this->pos; }

void CBaseEntity::SetHp(int new_hp) { this->hp = new_hp; }