#include <globals.h>
#include <turncontroller.h>

CTurnController::CTurnController() : turn_num(1) {}

IBaseEntity* CTurnController::GetExecutor() {
  return executor == nullptr ? nullptr : executor->entity;
}

void CTurnController::ShiftTurn(int num) {
  if (executor == nullptr) {
    executor = entity_list.GetHead();
  }

  while (num--) {
    if (executor->next == nullptr) {
      executor = entity_list.GetHead();
      continue;
    }
    executor = executor->next;
  }

  g_current_executor = executor->entity;
}

void CTurnController::ResetTurns() { turn_num = 1; }