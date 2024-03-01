#include <entity.h>

CObjProperties* IBaseEntity::GetProperties() { return &this->props; }

PosType* IBaseEntity::GetPos() { return &this->pos; }

void IBaseEntity::SetAnimation(const CBaseAnimation& new_animation) {
  animation = new_animation;
  animation.ResetTiming();
}

void IBaseEntity::PlayAnimation(const CBaseAnimation& new_animation) {

}