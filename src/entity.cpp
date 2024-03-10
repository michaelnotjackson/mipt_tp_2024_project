#include <entity.h>
#include <globals.h>

#include <thread>

CObjProperties* IBaseEntity::GetProperties() { return &this->props; }

PosType* IBaseEntity::GetPos() { return &this->pos; }

void MoveExecutor(IBaseEntity* entity, std::vector<PosType>* path) {
  g_move_in_process = true;
  if (!path) { return; }
  for (auto &pos: *path) {
    *entity->GetPos() = pos;
    SDL_Delay(g_move_speed);
  }
  delete path;
  g_move_in_process = false;
}

void IBaseEntity::MoveBy(std::vector<PosType>* path) {
  std::thread th(MoveExecutor, this, path);
  th.detach();
}

void IBaseEntity::SetAnimation(const CBaseAnimation& new_animation) {
  animation = new_animation;
  animation.ResetTiming();
}
void IBaseEntity::SetAnimation() {  // set default animation
  animation = default_animation;
  animation.ResetTiming();
}

void Watcher(IBaseEntity* ent, const CBaseAnimation& new_animation) {
  if (!ent) {
    return;
  }

  ent->SetAnimation(new_animation);
  ent->animation.ResetTiming();
  uint64_t start_tick = ent->animation.start_tick;
  SDL_Delay(new_animation.nFrames * new_animation.ticks_per_frame);

  if (ent->animation.start_tick == start_tick) {
    ent->SetAnimation();
  }
}

void IBaseEntity::PlayAnimation(const CBaseAnimation& new_animation) {
  std::thread th(Watcher, this, new_animation);
  th.detach();
}