#include <iostream>
#include <string>
#include "voc.h"
#include "player1.h"
#include "dice.h"

using namespace std;
using namespace GameSpace;

const int PlayerClass::DYING = -1;
const int PlayerClass::DISABLED = 0;
const int PlayerClass::DEAD = -10;
const string PlayerClass::DEFAULT_NAME = "DEFAULT";
const PlayerClass::RaceType PlayerClass::DEFAULT_RACE = HUMAN;
const int PlayerClass::NUM_RACES;
const int PlayerClass::NUM_HUMANOIDS;
const int PlayerClass::NUM_MONSTERS;
const string PlayerClass::RACE_STR[NUM_RACES] = {"HUMAN", "ELF", "ORC", "TROLL",
                                                 "OGRE"};

const int PlayerClass::AB_ADJ[NUM_RACES][NUM_ABILITIES] = {

    //         DEX  CON  INT  CHA  STR  WIS
    /*HUMAN*/ {0, 0, 0, 0, 0, 0},
    /*ELF*/ {2, -2, 0, 0, 0, 0},
    /*ORC*/ {0, 0, -2, -2, 2, -1},
    /*TROLL*/ {14, 23, 6, 6, 23, 9},
    /*OGRE*/ {8, 15, 6, 7, 21, 10}};

int PlayerClass::Abilities[NUM_ABILITIES] =

    //        DEX  CON  INT  CHA  STR  WIS
    /*Player*/ {0, 0, 0, 0, 0, 0};

// CONSTRUCTORS

PlayerClass::PlayerClass() {
  name = DEFAULT_NAME;
  race = DEFAULT_RACE;
  voc = VocRules::FTR;
  SetStats();
  SetHP();
  SetAbilities(race);
}

PlayerClass::PlayerClass(string newName) {
  SetName(newName);
  race = DEFAULT_RACE;
  voc = VocRules::FTR;
  SetStats();
  SetHP();
  SetAbilities(race);
}

PlayerClass::PlayerClass(string n, RaceType r) {
  bool isMonster;

  SetName(n);
  SetRace(r);
  isMonster = IsMonster();

  if (isMonster == true) {
    voc = VocRules::NNE;
    SetMonsterStats();
    return;
  }

  else

  {
    voc = VocRules::FTR;
    SetStats();
    SetHP();
    SetAbilities(race);
  }

  return;
}

PlayerClass::PlayerClass(string n, RaceType r, VocRules::VocType v) {
  bool isMonster;

  SetName(n);
  SetRace(r);
  isMonster = IsMonster();
  if (isMonster == true) {
    voc = VocRules::NNE;
    SetMonsterStats();
    return;
  } else

    SetVoc(v);
  SetStats();
  SetHP();
  SetAbilities(race);

  return;
}

void PlayerClass::SetVoc(VocRules::VocType v) {
  if (v > VocRules::NUM_VOC or v < 0) {
    voc = VocRules::FTR;
  }

  else

      if (IsHummanoid() == true and v == VocRules::NNE) {
    voc = VocRules::FTR;
  }

  else

  {
    voc = v;
  }

  return;
}

void PlayerClass::SetMonsterStats() {
  int i;
  RaceType a;

  if (race == TROLL) {
    maxHP = Dice::Roll(name, GameSpace::HP, 3, 6);
    maxHP = maxHP + 36;
    currentHP = maxHP;
    for (i = 0; i <= NUM_ABILITIES; i++) {
      Abilities[i] = Abilities[i] + AB_ADJ[race][i];
      a + 1;
    }
    SetStats();
  }

  if (race == OGRE) {
    maxHP = Dice::Roll(name, GameSpace::HP, 4, 8);
    maxHP = maxHP + 8;
    currentHP = maxHP;
    for (i = 0; i <= NUM_ABILITIES; i++) {
      Abilities[i] = Abilities[i] + AB_ADJ[race][i];
      a + 1;
    }
    SetStats();
  }
}

void PlayerClass::SetRace(RaceType r) {
  if (r > NUM_RACES or r < 0) {
    race = DEFAULT_RACE;
  }

  else

    race = r;

  return;
}

void PlayerClass::SetName(string newName) {
  if (newName < "1") {
    name = DEFAULT_NAME;
  }

  else

    name = newName;
}

void PlayerClass::SetHP() {
  SetHitDie();
  maxHP = Dice::Roll(name, GameSpace::HP, 1, hitDie);
  currentHP = maxHP;

  return;
}

void PlayerClass::SetStats() {
  vocLevel = 1;
  row = -1;
  col = -1;
  level = 1;
  xp = 0;

  return;
}

string PlayerClass::Name() { return name; }

int PlayerClass::Race() { return race; }

int PlayerClass::XP() { return xp; }

int PlayerClass::Row() { return row; }

int PlayerClass::Col() { return col; }

int PlayerClass::Level() { return level; }

int PlayerClass::HP() { return currentHP; }

int PlayerClass::MaxHP() { return maxHP; }

bool PlayerClass::IsMonster() {
  if ((race == TROLL) or (race == OGRE)) {
    return true;

  }

  else {
    return false;
  }
}

bool PlayerClass::IsHummanoid() {
  if ((race == TROLL) or (race == OGRE))

  {
    return false;
  }

  else

  {
    return true;
  }
}

bool PlayerClass::SetCell(int newRow, int newCol) {
  bool checkCell;

  checkCell = Check(newRow, newCol);

  if (checkCell == true) {
    col = newCol;
    row = newRow;
    return true;
  }

  else {
    return false;
  }
}

bool PlayerClass::Check(int newRow, int newCol) {
  if (newRow > -1 and newCol > -1) {
    if (newRow <= 10 and newCol <= 10) {
      return true;
    }
  }

  if (newRow == -1 and newCol == -1) {
    return true;
  }

  else {
    return false;
  }
}

bool PlayerClass::IsDisabled() {
  if (currentHP <= DISABLED) {
    return true;
  }

  else {
    return false;
  }
}

bool PlayerClass::IsDying() {
  if (currentHP <= DYING) {
    return true;
  }

  else {
    return false;
  }
}

bool PlayerClass::IsDead() {
  if (currentHP <= DEAD) {
    return true;
  }

  else {
    return false;
  }
}

string PlayerClass::RaceStr() {
  string raceStr;

  raceStr = RACE_STR[race];

  return raceStr;
}

int PlayerClass::SetHitDie() {
  VocRules *vrPtr = VocRules::GetVocRules();
  hitDie = vrPtr->VocRules::HitDie(voc);

  return hitDie;
}

int PlayerClass::UpdateXP(int value) {
  int updatedHP;

  VocRules *vrPtr = VocRules::GetVocRules();

  if (value <= 0) {
    return xp;
  }

  if (value >= vrPtr->XPforPromotion(level)) {
    level++;
    xp = xp + value;
    updatedHP = Dice::Roll(name, GameSpace::HP, 1, hitDie);
    maxHP = maxHP + updatedHP;
    currentHP = maxHP;
    return xp;
  }

  else if (value < vrPtr->XPforPromotion(level)) {
    xp = xp + value;
    return xp;
  }
}

int PlayerClass::UpdateHP(int modification) {
  int totalHP;

  totalHP = currentHP + modification;
  if (totalHP > maxHP) {
    return currentHP;
  }

  else {
    currentHP = totalHP;
    return totalHP;
  }
}

void PlayerClass::SetAbilities(RaceType race) {
  int i = 0;
  GameSpace::RollType a;

  for (i = 0; i <= NUM_ABILITIES; i++) {
    Abilities[i] = Abilities[i] + Dice::Roll(name, a, 3, 6);
    Abilities[i] = Abilities[i] + AB_ADJ[race][i];
    a + 1;
  }

  return;
}

int PlayerClass::Ability(AbilityType ability) {
  int abilityNum;

  abilityNum = Abilities[ability];

  return abilityNum;
}

int PlayerClass::AbilityMod(AbilityType ability) {
  int abilityMod;

  abilityMod = AB_ADJ[race][ability];

  return abilityMod;
}

string PlayerClass::VocStr() {
  string vocStr;

  vocStr = VocRules::VocToStr(voc);

  return vocStr;
}

void PlayerClass::Write() {
  string vocString;
  string raceString;

  vocString = VocStr();
  raceString = RaceStr();

  cout << raceString << '#' << vocString << '#' << level << '#' << name << '#'
       << '(' << row << ',' << col << ')' << '#' << maxHP << '#' << currentHP
       << '#'

       << '[';
  OutputAbil();
  cout << ']';

  return;
}

void PlayerClass::OutputAbil() {
  int i;

  for (i = 0; i < NUM_ABILITIES; i++) {
    cout << Abilities[i] << '#';
  }
}
