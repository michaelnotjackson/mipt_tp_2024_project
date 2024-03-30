#include <dice_roller.h>
#include <playable_classes.h>
#include <playable_races.h>
#include <player.h>

CBasePlayer::CBasePlayer(CBaseAnimation& animation, ClassType player_class,
                         RaceType player_race, const std::string& name,
                         int team)
    : IBaseEntity(animation) {
  props = playable_classes[player_class];
  props.merge(playable_races[player_race]);

  props["s_name"] = name;
  props["i_team"] = team;

  for (int _times = 0; _times < 6; ++_times) {
    int dices[4];
    for (int& dice : dices) {
      dice =
          CDiceRoller::RollDice("characteristics " + std::to_string(_times), 6);
    }
    std::sort(dices, dices + 4);

    characteristics[_times] = dices[0] + dices[1] + dices[2];
    SDL_Log("%s %i %s %i", "Characteristic", _times, "is set to",
            characteristics[_times]);
  }

  props["i_health"] =
      10 + characteristics[(int)(GetPropValue<CharacteristicType>(
               props, "c_health_lvl_modifier"))];
  SDL_Log("%s %i", "Health is set to", GetPropValue<int>(props, "i_health"));
}