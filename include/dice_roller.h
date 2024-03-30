#pragma once

#include <string>

#include <globals.h>

class CDiceRoller {
 public:
  static int RollDice(const std::string& name, int sides);
};
