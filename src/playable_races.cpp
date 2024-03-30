#include <playable_races.h>

std::map<RaceType, CObjProperties> playable_races(
    {{RaceType::human,
      {{"v_race_characteristic_modifiers",
        std::vector<int>({1, 1, 1, 1, 1, 1})},
       {"i_base_speed", 30}}}});