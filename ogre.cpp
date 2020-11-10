#include "ogre.h"

using namespace std;
using namespace GameSpace;

const int Ogre::ABIL_ADJ[6] = {8, 15, 6, 7, 21, 10};
const int Ogre::HIT_DICE[3] = {4, 8, 8};
const int Ogre::SAVE_THROW[3] = {6, 0, 1};
const int Ogre::BASE_ATTACK_BONUS[2] = {1, 8};
const int NUM_INIT_SKILLS = 3;
const int NUM_INIT_WPN = 1;
const string Ogre::INIT_SKILLS[NUM_INIT_SKILLS] = {"INTIMIDATE", "LISTEN",
                                                   "SPOT"};
const string Ogre::INITIAL_WPN = "Spear";
const string Ogre::RACE = "OGRE";



Ogre* Ogre:: Clone() const { 
    return new Ogre(*this); 
}







void Ogre::InitSkills() {
  for (int i = 0; i < NUM_INIT_SKILLS; i++) {
    PlayerClass::AddSkill(INIT_SKILLS[i]);
  }

  return;
}

void Ogre::Write(ostream& out) const {
  out << Ogre::RaceStr();
  Monster::Write(out);

  return;
}

string Ogre::RaceStr() const { return RACE; }

Ogre::Ogre(string name) : Monster(name, ABIL_ADJ, HIT_DICE) {
  Ogre::InitSkills();
}

int Ogre::RollSavingThrow(SavingThrowType kind) const {
  Monster::RollSavingThrow(kind, SAVE_THROW);
}

int Ogre::RollAttack() const { Monster::RollAttack(BASE_ATTACK_BONUS); }

vector<string> Ogre::InitialWeaponList() const {
  vector<string> rv;

  for (int i = 0; i < NUM_INIT_WPN; i++) {
    rv.push_back(INITIAL_WPN);
  }

  return rv;
}
