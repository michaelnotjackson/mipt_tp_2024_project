#include <playable_races.h>

std::map<RaceType, CObjProperties> playable_races(
    {{RaceType::human,
      {{"v_race_characteristic_modifiers",
        {PropValueType::VECTOR_INT, new std::vector<int>({1, 1, 1, 1, 1, 1})}},
       {"i_base_speed", {PropValueType::INT, new int(30)}}}}});