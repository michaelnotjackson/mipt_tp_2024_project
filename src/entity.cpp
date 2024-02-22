#include <entity.h>

BaseEntity::BaseEntity():  hp(0),
               pos(0, 0),
               size(SizeType::MEDIUM),
               sprite(),
               obstacle_degree(ObstacleType::HALF_SPEED) {}

int BaseEntity::GetHp() { return this->hp; }
PosType BaseEntity::GetPos() { return this->pos; }

void BaseEntity::ChangeHp(int new_hp) { this->hp = new_hp; }