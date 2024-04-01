#pragma once

#include "entitylist.h"

class CTurnController {
 int turn_num;
 CEntityNode* executor;
 public:
  CTurnController();

 public:
  int GetTurn() const;

  IBaseEntity* GetExecutor();

  void ShiftTurn(int num = 1);

  void ResetTurns();
};