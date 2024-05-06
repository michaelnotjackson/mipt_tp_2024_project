#include "include/engine/dice_roller.h"

#include <random>

#include "include/SDL/include/SDL.h"

int CDiceRoller::RollDice(const std::string& name, int sides) {
  std::uniform_int_distribution<int> dist(1, sides);

  int result = dist(g_rng);

  if (!name.empty()) {
    SDL_Log("%s %s%i %s %i", name.c_str(), "rolled d", sides,
            "with result:", result);
  }

  return result;
}