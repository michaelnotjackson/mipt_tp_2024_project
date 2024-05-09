#include "include/engine/entity.h"

#include <engine/assets_storage.h>

#include <thread>

#include "include/engine/globals.h"
#include "include/engine/utils.h"

IBaseEntity::IBaseEntity(CBaseAnimation &animation)
    : default_animation(animation), animation(animation) {}

CObjProperties *IBaseEntity::GetProperties() { return &this->props; }

PosType *IBaseEntity::GetPos() { return &this->pos; }

void MoveExecutor(IBaseEntity *entity, std::vector<PosType> *path) {
  g_move_in_process = true;
  g_current_room.field[entity->GetPos()->y][entity->GetPos()->x]->entity_on =
      nullptr;
  if (!path) {
    return;
  }
  for (auto &pos : *path) {
    *entity->GetPos() = pos;
    SDL_Delay(g_move_speed);
  }
  path->clear();
  g_current_room.field[entity->GetPos()->y][entity->GetPos()->x]->entity_on =
      entity;
  RecalculatePath();
  g_move_in_process = false;
}

void MoveExecutorShared(IBaseEntity *entity,
                        const std::shared_ptr<std::vector<PosType>> &path) {
  g_move_in_process = true;
  g_current_room.field[entity->GetPos()->y][entity->GetPos()->x]->entity_on =
      nullptr;
  if (path.get() == nullptr) {
    return;
  }
  for (auto &pos : *path) {
    *entity->GetPos() = pos;
    SDL_Delay(g_move_speed);
  }
  path->clear();
  g_current_room.field[entity->GetPos()->y][entity->GetPos()->x]->entity_on =
      entity;
  RecalculatePath();
  g_move_in_process = false;
}

void IBaseEntity::MoveBy(std::vector<PosType> *path) {
  std::thread th(MoveExecutor, this, path);
  th.detach();
}
void IBaseEntity::MoveBy(const std::shared_ptr<std::vector<PosType>> &path) {
  std::thread th(MoveExecutorShared, this, path);
  th.detach();
}

void IBaseEntity::SetAnimation(const CBaseAnimation &new_animation) {
  animation = new_animation;
  animation.ResetTiming();
}
void IBaseEntity::SetAnimation() { // set default animation
  animation = default_animation;
  animation.ResetTiming();
}

void Watcher(IBaseEntity *ent, const CBaseAnimation &new_animation) {
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

void IBaseEntity::PlayAnimation(const CBaseAnimation &new_animation) {
  std::thread th(Watcher, this, new_animation);
  th.detach();
}

void AttackExecutor(PosType enemy_pos) {
  while (*g_current_executor->GetPos() != g_current_path.back() &&
         !g_current_path.empty()) {
  }
  if (g_current_room.field[enemy_pos.y][enemy_pos.x]->entity_on != nullptr) {
    g_current_executor->PlayAnimation(assets_manager.GetAnimation(
        "animations/warriors/warrior_blue/attack2_right"));

    std::get<int>(g_current_room.field[enemy_pos.y][enemy_pos.x]
                      ->entity_on->props["i_health"]) -=
        5; // TODO Weapon damage

    if (std::get<int>(g_current_room.field[enemy_pos.y][enemy_pos.x]
                            ->entity_on->props["i_health"]) <= 0) {
        g_current_room.field[enemy_pos.y][enemy_pos.x]->entity_on->PlayAnimation(
            assets_manager.GetAnimation("animations/warriors/death"));
      SDL_Delay(10);

      while (
          g_current_room.field[enemy_pos.y][enemy_pos.x]->entity_on->animation !=
          g_current_room.field[enemy_pos.y][enemy_pos.x]
              ->entity_on->default_animation) {}
      g_current_room.field[enemy_pos.y][enemy_pos.x]->entity_on->PlayAnimation(
            assets_manager.GetAnimation("animations/warriors/skull_disappear"));
      SDL_Delay(10);

      while (
          g_current_room.field[enemy_pos.y][enemy_pos.x]->entity_on->animation !=
          g_current_room.field[enemy_pos.y][enemy_pos.x]
              ->entity_on->default_animation) {}
       entity_list.RemoveByIndex(entity_list.GetIndByPos(SDL_Rect{enemy_pos.x, enemy_pos.y,0,0}));
    }
}
  g_current_action = ActionType::FREE;
}

void IBaseEntity::Attack(PosType enemy_pos) {
  std::thread th(AttackExecutor, enemy_pos);
  th.detach();
}
