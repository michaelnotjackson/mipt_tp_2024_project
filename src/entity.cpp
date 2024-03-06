#include <entity.h>

#include <thread>

CObjProperties* IBaseEntity::GetProperties() { return &this->props; }

PosType* IBaseEntity::GetPos() { return &this->pos; }

void IBaseEntity::SetAnimation(const CBaseAnimation& new_animation) {
  animation = new_animation;
  animation.ResetTiming();
}
void IBaseEntity::SetAnimation() { //set default animation
  animation = default_animation;
  animation.ResetTiming();
}

void IBaseEntity::PlayAnimation(const CBaseAnimation& new_animation) {
  {
    SetAnimation(new_animation);
    while ( (SDL_GetTicks64() - new_animation.start_tick) != (new_animation.nFrames * new_animation.ticks_per_frame) ) {
//      SDL_Log("%s", "1");
    }
    SetAnimation();
  }
}