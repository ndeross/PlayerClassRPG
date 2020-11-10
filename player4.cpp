#include "player4.h"

using namespace std;
using namespace GameSpace;

PlayerClass::MapType PlayerClass::skillMap;
const int PlayerClass::VOC_DICE;
const int PlayerClass::VOC_FACES;
const int PlayerClass::DEFENSE_ADJ;
bool PlayerClass::mapLoaded = false;

int PlayerClass::Ability(AbilityType abil) const { return Abil[abil]; }

string PlayerClass::Name() const {return NAME;}

int PlayerClass::Row() const { return row; }

int PlayerClass::Col() const { return col; }

int PlayerClass::HP() const { return currentHP; }

int PlayerClass::MaxHP() const { return maxHP; }


PlayerClass::PlayerClass(string initName, const int ABIL_ADJ[], bool doRoll)
    :NAME(InitName(initName)) {
  row = -1;
  col = -1;
  currentHP = 1;
  maxHP = 1;
  weapon = NULL;
  InitAbilities(ABIL_ADJ, doRoll);

  if (PlayerClass::mapLoaded == false) {
    PlayerClass::skillMap = LoadSkillTable();
  }
}




PlayerClass::~PlayerClass() {
  delete weapon;
  weapon = NULL;
}


void PlayerClass::InitHP(const int HIT_DIE[3]) {
int hd;


maxHP = Dice::Roll(NAME, GameSpace::HP, HIT_DIE[0], HIT_DIE[1]) + (HIT_DIE[2]); 
 
      
  if (maxHP <= 0) {
    maxHP = 1;
  }

  currentHP = maxHP;
}



Weapon* PlayerClass::CurrentWeapon() const { return weapon; }

vector<int> PlayerClass::Abilities() const {
  vector<int> abil;

  for (int i = 0; i < NUM_ABILITIES; i++)

  {
    abil.push_back(Abil[i]);
  }

  return abil;
}

int PlayerClass::AbilityMod(AbilityType abil) const {
  int abilityMod;

  abilityMod = (Abil[abil] / 2) - 5;

  return abilityMod;
}

int PlayerClass::WhichMod(SavingThrowType kindOfThrow) {
  int ability = 0;

  if (kindOfThrow == FORT) {
    ability = AbilityMod(CON);
  }

  if (kindOfThrow == WILL) {
    ability = AbilityMod(WIS);
  }

  if (kindOfThrow == REFLEX) {
    ability = AbilityMod(DEX);
  }

  return ability;
}

string PlayerClass::WeaponName() const {
  string rv;

  if (weapon == NULL) {
    rv = "";
  }

  else

    rv = weapon->Weapon::Name();

  return rv;
}

string PlayerClass::WeaponNameAndNum() const {
  string rv;

  if (weapon == NULL) {
    rv = "";
  }

  else

    rv = weapon->NameAndNum();

  return rv;
}

vector<string> PlayerClass::Skills() const

{
  return mySkills;
}

bool PlayerClass::IsActive() const { return (currentHP > 0); }

bool PlayerClass::IsDisabled() const { return (currentHP <= DISABLED); }

bool PlayerClass::IsDying() const { return (currentHP <= DYING); }

bool PlayerClass::IsDead() const { return (currentHP <= DEAD); }

bool PlayerClass::HasWeapon() const { return (weapon != NULL); }

int PlayerClass::UpdateHP(int modification) {
  int totalHP;

  if (!IsDead()) {
    totalHP = (currentHP) + (modification);
    if (totalHP > maxHP) {
      currentHP = maxHP;
    } else {
      currentHP = totalHP;
    }
  }

  return currentHP;
}

bool PlayerClass::CheckCell(int newRow, int newCol) {
  if (newRow > -1 and newCol > -1) {
    if (newRow <= MAX_ROWS and newCol <= MAX_COLS) {
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

bool PlayerClass::SetCell(int newRow, int newCol) {
  bool voidCell;

  voidCell = CheckCell(newRow, newCol);

  if (voidCell == true) {
    col = newCol;
    row = newRow;
    return true;
  }

  else {
    return false;
  }
}

int PlayerClass::SkillCheck(string skill) const {
  MapType compareSkills;
  vector<string>::const_iterator iter;
  MapType::iterator iterMap;
  int skillThrow = 0;
  string aSkill;
  AbilityType abil;
  int save;
  string bSkill;
  bool validSkill = PlayerClass::ValidSkill(skill);

  if (validSkill == false) {
    throw INVALID_SKILL;
  }

  if (IsDead()) {
    skillThrow = 0;
  }

  else {
    for (iter = mySkills.begin(); iter != mySkills.end(); ++iter)

    {
      for (iterMap = skillMap.begin(); iterMap != skillMap.end(); ++iterMap) {
        aSkill = iterMap->first;
        abil = iterMap->second;
        bSkill = *iter;

        if (Ucase(skill) == Ucase(bSkill)) {
          if (Ucase(skill) == Ucase(aSkill)) {
            save = Dice::Roll(NAME, SKCK, 1, 20);
            skillThrow = save + AbilityMod(abil);
            return skillThrow;
          }
        }
      }
    }
  }
  return skillThrow;
}

bool PlayerClass::ValidSkill(string skill) const {
  bool found = false;
  string aSkill, ability;
  MapType::const_iterator iter;

  if (skill == "") {
    found = true;
  }

  else

    for (iter = PlayerClass::skillMap.begin();
         iter != PlayerClass::skillMap.end(); ++iter)

    {
      aSkill = iter->first;

      if (Ucase(skill) == Ucase(aSkill)) {
        found = true;
      }
    }

  return found;
}

bool PlayerClass::AddSkill(string skill) {
  vector<string>::iterator iter;
  bool found = false;

  skill = Ucase(skill);
  for (iter = mySkills.begin(); iter != mySkills.end(); ++iter) {
    if (Ucase(*iter) == skill) {
      found = true;
    }
  }

  if (ValidSkill(skill)) {
    if (found == false) {
      if (IsActive()) {
        if (skill != "") {
          mySkills.push_back(skill);
          found = true;
        }
      }
    }
  }

  else {
    throw INVALID_SKILL;
  }

  Sort(mySkills);
  return found;
}

void PlayerClass::Amnesia() {
  mySkills.clear();

  return;
}

Weapon* PlayerClass::LoseWeapon() {
  Weapon* rv;

  if (weapon == NULL) {
    rv = weapon;
  }

  if (weapon != NULL) {
    rv = weapon;
    weapon = NULL;
  }

  return rv;
}

Weapon* PlayerClass::FindWeapon(Weapon* wpn) {
  Weapon* rv;

  if (!IsActive()) {
    rv = wpn;
  }

  else

  {
    if (wpn == NULL) {
      rv = NULL;
    } else {
      rv = weapon;
      weapon = wpn;
    }
  }
  return rv;
}

int PlayerClass::RollInitiative() const {
  int init;

  init = Dice::Roll(NAME, INIT, DEFAULT_DICE, DEFAULT_FACES);

  init = init + AbilityMod(DEX);

  return init;
}

int PlayerClass::RollAttack() const { return 0; }

int PlayerClass::RollSavingThrow(SavingThrowType kind) const { return 0; }

int PlayerClass::RollDefense() const {
  int def;

  def = DEFENSE_ADJ + AbilityMod(DEX);

  return def;
}

int PlayerClass::RollDamage() const {
  int damage = 0;

  if (weapon == NULL) {
    damage = (AbilityMod(STR));
  } else if (weapon->IsMelee()) {
    damage = weapon->RollWeaponDamage(NAME) + (AbilityMod(STR));
  } else if (weapon->IsRange()) {
    damage = weapon->RollWeaponDamage(NAME);
  }

  if (damage < 0) {
    damage = 0;
  }

  return damage;
}

void PlayerClass::OutputSkills(ostream& out) const {
  vector<string>::const_iterator iter;

  if (mySkills.size() == 0) {
    return;
  }

  for (iter = mySkills.begin(); iter < mySkills.end(); ++iter) {
    if (iter != mySkills.end() - 1) {
      out << *iter << ',';
    }

    else {
      out << *iter;
    }
  }
}


 void PlayerClass:: UpdateMaxHP(int value) { 
     
if (value > 0) { 
    maxHP += value;
    currentHP = maxHP; 
} 

else 
    
return; 
     
} 


bool PlayerClass::operator==(const PlayerClass& p) const {
  return (Ucase(NAME) == Ucase(p.NAME));
}

bool PlayerClass::operator!=(const PlayerClass& p) const {
  bool rv;

  return (Ucase(NAME) != Ucase(p.NAME));
}

bool PlayerClass::operator<(const PlayerClass& p) const {
  return (Ucase(NAME) < Ucase(p.NAME));
}

bool PlayerClass::operator<=(const PlayerClass& p) const {
  return (Ucase(NAME) <= Ucase(p.NAME));
}

bool PlayerClass::operator>(const PlayerClass& p) const {
  return (Ucase(NAME) > Ucase(p.NAME));
}

bool PlayerClass::operator>=(const PlayerClass& p) const {
  return (Ucase(NAME) >= Ucase(p.NAME));
}

PlayerClass::PlayerClass(const PlayerClass& p) : weapon(NULL), NAME(p.NAME) {
  CopyPlayer(p);
}

void PlayerClass::CopyPlayer(const PlayerClass& p) {
  delete weapon;
  weapon = NULL;

  *const_cast<string*>(&NAME) = p.NAME;

  row = p.row;
  col = p.col;
  maxHP = p.maxHP;
  currentHP = p.currentHP;

  for (int i = 0; i <= NUM_ABILITIES; i++) {
    Abil[i] = p.Abil[i];
  }

  if (p.HasWeapon()) {
    weapon = new Weapon(*p.weapon);
  }

  else {
    weapon = NULL;
  }

  mySkills = p.mySkills;

  return;
}

void PlayerClass::InitSkills(vector<string> skills) {}


void PlayerClass::InitAbilities(const int ABIL_ADJ[NUM_ABILITIES], bool roll) {
  int i = 0;
  int diceRoll;

  if (roll) {
    for (i = 0; i < NUM_ABILITIES; i++) {
      Abil[i] =
          ABIL_ADJ[i] + (Dice::Roll(NAME, static_cast<GameSpace::RollType>(i),
                                    VOC_DICE, VOC_FACES));
    }
  }

  else

    for (i = 0; i < NUM_ABILITIES; i++) {
      Abil[i] = ABIL_ADJ[i];
    }
  return;
}

int PlayerClass::RollHitDie(int numRolls, int faces, int mod) const {}

bool PlayerClass::operator=(const PlayerClass& p) { CopyPlayer(p); }

bool PlayerClass::ValidThrow(SavingThrowType kindOfThrow) const {
  bool goodThrow = true;

  {
    if ((kindOfThrow < 0) or (kindOfThrow > NUM_SAVINGTHROW)) {
      goodThrow = false;
    }
  }

  return goodThrow;
}

int PlayerClass::WhichMod(SavingThrowType kindOfThrow) const {
  int ability = 0;

  if (kindOfThrow == FORT) {
    ability = AbilityMod(CON);
  }

  else

      if (kindOfThrow == WILL) {
    ability = AbilityMod(WIS);
  }

  else

      if (kindOfThrow == REFLEX) {
    ability = AbilityMod(DEX);
  }

  return ability;
}

string PlayerClass::InitName(string newName) {
  newName = TrimStr(newName);

  if (newName == "") {
    throw INVALID_NAME;
  }

  if (newName.size() > 10)

  {
    newName = newName.substr(0, 10);
  }

  newName = TrimStr(newName);

  return newName;
}

PlayerClass::AbilityType PlayerClass::StrToAbility(string s) {
  AbilityType abil;
  s = GameSpace::Ucase(s);
  if (s == "DEX")
    abil = DEX;
  else if (s == "CON")
    abil = CON;
  else if (s == "INT")
    abil = INT;
  else if (s == "CHA")
    abil = CHAR;
  else if (s == "STR")
    abil = STR;
  else if (s == "WIS")
    abil = WIS;
  return abil;
}

PlayerClass::MapType PlayerClass::LoadSkillTable() {
  MapType skillsMap;
  string aSkill, ability;
  AbilityType abil;
  ifstream fin;
  fin.open(GameSpace::SKILLS_FILE.c_str());

  getline(fin, aSkill, '#');
  getline(fin, ability);
  while (fin) {
    abil = StrToAbility(ability);

    PlayerClass::skillMap.insert(make_pair(aSkill, abil));

    getline(fin, aSkill, '#');
    getline(fin, ability);
  }
  fin.close();

  PlayerClass::mapLoaded = true;

  return skillMap;
}

void PlayerClass::Write(ostream& out) const {
  string wpnName;
  vector<string>::const_iterator iter;

  if (weapon != NULL) {
    wpnName = PlayerClass::WeaponNameAndNum();
  }

  else

      if (weapon == NULL) {
    wpnName = "";
  }

  out << '#' << PlayerClass::Name() << '#' << '(' << PlayerClass::Row() << ','
      << PlayerClass::Col() << ')' << '#' << PlayerClass::HP() << '#'
      << PlayerClass::MaxHP() << '#' << '[' << PlayerClass::Ability(DEX) << '#'
      << PlayerClass::Ability(CON) << '#' << PlayerClass::Ability(INT) << '#'
      << PlayerClass::Ability(CHAR) << '#' << PlayerClass::Ability(STR) << '#'
      << PlayerClass::Ability(WIS) << ']' << '#' << wpnName << '#' << '(';

  OutputSkills(out);

  out << ')';
  out << '#';
  out << endl;
  return;
}

ostream& operator<<(ostream& out, const PlayerClass* p) {
  p->Write(out);
  return out;
}
