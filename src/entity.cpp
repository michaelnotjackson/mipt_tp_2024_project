#include <entity.h>

CBaseEntity::CBaseEntity()
    : hp(0),
      pos(0, 0),
      size(SizeType::MEDIUM),
      sprite(),
      obstacle_degree(ObstacleType::HALF_SPEED) {}

int CBaseEntity::GetHp() { return this->hp; }
PosType CBaseEntity::GetPos() { return this->pos; }

void CBaseEntity::SetHp(int new_hp) { this->hp = new_hp; }