#include "include/engine/turn_controller.h"

#include "include/engine/globals.h"

CTurnController::CTurnController() : turn_num(1) {}

IBaseEntity* CTurnController::GetExecutor() {
  return executor == nullptr ? nullptr : executor->entity;
}

void CTurnController::ShiftTurn(int num) {
  g_mutex.lock();
  if (executor == nullptr) {
    executor = entity_list.GetHead();
  }

  while (num) {
    if (executor->next == nullptr) {
      executor = entity_list.GetHead();
    } else {
      executor = executor->next;
    }
    if (entity_list.deleted[executor]) {
      continue;
    }
    num -= GetPropValue<int>(executor->entity->props, "i_team") != 0;
  }

  g_current_executor = executor->entity;
  g_mutex.unlock();
}

void CTurnController::ResetTurns() { turn_num = 1; }