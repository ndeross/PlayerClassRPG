#include "troll.h"

using namespace std;
using namespace GameSpace;

const int Troll::ABIL_ADJ[6] = {14, 23, 6, 6, 23, 9};
const int Troll::HIT_DICE[3] = {6, 8, 36};
const int Troll::SAVE_THROW[3] = {11, 4, 3};
const int Troll::BASE_ATTACK_BONUS[2] = {1, 9};
const string Troll::INIT_SKILLS[NUM_INIT_SKILLS] = {"Listen", "Spot"};
const string Troll::INITIAL_WPN = "Club";
const string Troll::RACE = "TROLL";

void Troll::InitSkills() {
  for (int i = 0; i < NUM_INIT_SKILLS; i++) {
    PlayerClass::AddSkill(INIT_SKILLS[i]);
  }
  return;
}

void Troll::Write(ostream& out) const {
  out << Troll::RaceStr();
  Monster::Write(out);

  return;
}

string Troll::RaceStr() const { return RACE; }

Troll::Troll(string name) : Monster(name, ABIL_ADJ, HIT_DICE) { InitSkills(); }

int Troll::RollSavingThrow(SavingThrowType kind) const {
  Monster::RollSavingThrow(kind, SAVE_THROW);
}


Troll* Troll:: Clone() const { 
    return new Troll(*this); 
}




int Troll::RollAttack() const { Monster::RollAttack(BASE_ATTACK_BONUS); }

vector<string> Troll::InitialWeaponList() const {
  vector<string> rv;

  for (int i = 0; i < NUM_INIT_WPN; i++) {
    rv.push_back(INITIAL_WPN);
  }

  return rv;
}
