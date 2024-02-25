#include <player.h>

#include <utility>

void CBasePlayer::ChangeName(std::string name) { this->name = name; }
void CBasePlayer::SetLvl(int lvl) { this->lvl = lvl; }
void CBasePlayer::SetMana(int mana) { this->mp = mana; }
void CBasePlayer::SetMaxCarryWeight(double weight) {
  this->max_carry_weight = max_carry_weight;
}
void CBasePlayer::SetTeam(int team_id) { this->team_id = team_id; }
void CBasePlayer::SetXp(int xp) { this->xp = xp; }

ClassType CBasePlayer::GetClass() { return this->ply_class; }
int CBasePlayer::GetLvl() { return this->lvl; }
int CBasePlayer::GetMana() { return this->mp; }
double CBasePlayer::GetMaxCarryWeight() { return this->max_carry_weight; }
std::string CBasePlayer::GetName() { return this->name; }
RaceType CBasePlayer::GetRace() { return this->race; }
int CBasePlayer::GetTeam() { return this->team_id; }
int CBasePlayer::GetXp() { return this->xp; }

CBasePlayer::CBasePlayer(RaceType race, ClassType ply_class, int spell_list,
               int inventory, std::string name, int team_id)
    : race(race),
      ply_class(ply_class),
      spell_list(spell_list),
      inventory(inventory),
      name(std::move(name)),
      team_id(team_id){};
