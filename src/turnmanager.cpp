#include <globals.h>
#include <turnmanager.h>

CTurnManager::CTurnManager() : turn_num(1) {}

IBaseEntity* CTurnManager::GetExecutor() {
  return executor == nullptr ? nullptr : executor->entity;
}

void CTurnManager::ShiftTurn(int num) {
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

void CTurnManager::ResetTurns() { turn_num = 1; }