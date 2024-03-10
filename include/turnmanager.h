#pragma once

#include <entitylist.h>

class CTurnManager {
 int turn_num;
 CEntityNode* executor;
 public:
  CTurnManager();

 public:
  int GetTurn() const;

  IBaseEntity* GetExecutor();

  void ShiftTurn(int num = 1);

  void ResetTurns();
};