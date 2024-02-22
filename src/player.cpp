#include <player.h>

#include <utility>

void Player::ChangeName(std::string name) { this->name = name; }
void Player::SetLvl(int lvl) { this->lvl = lvl; }
void Player::SetMana(int mana) { this->mp = mana; }
void Player::SetMaxCarryWeight(double weight) {
  this->max_carry_weight = max_carry_weight;
}
void Player::SetTeam(int team_id) { this->team_id = team_id; }
void Player::SetXp(int xp) { this->xp = xp; }

ClassType Player::GetClass() { return this->ply_class; }
int Player::GetLvl() { return this->lvl; }
int Player::GetMana() { return this->mp; }
double Player::GetMaxCarryWeight() { return this->max_carry_weight; }
std::string Player::GetName() { return this->name; }
RaceType Player::GetRace() { return this->race; }
int Player::GetTeam() { return this->team_id; }
int Player::GetXp() { return this->xp; }

Player::Player(RaceType race, ClassType ply_class, int spell_list,
               int inventory, std::string name, int team_id)
    : race(race),
      ply_class(ply_class),
      spell_list(spell_list),
      inventory(inventory),
      name(std::move(name)),
      team_id(team_id){};
