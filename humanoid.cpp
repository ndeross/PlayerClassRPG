#include "humanoid.h"
#include "pack.h"

using namespace std;
using namespace GameSpace;

const int Humanoid::MAX_SKILL;
const int Humanoid::NUM_LEVELS;

const string Humanoid::INITIAL_SKILLS[VocRules::NUM_VOC][MAX_SKILL] = {

    /*NNE*/ {"", "", ""},
    /*BBM*/ {"CLIMB", "LISTEN", "SWIM"},
    /*CLR*/ {"HEAL", "USE MAGIC DEVICES", ""},
    /*FTR*/ {"INTIMIDATE", "SWIM", ""},
    /*ROG*/ {"BLUFF", "CLIMB", "HIDE"},
    /*WIZ*/ {"CONCENTRATION", "HIDE", "USE MAGIC DEVICES"}

};

Humanoid::~Humanoid() {
    
    delete pack; 
}

VocRules::VocType Humanoid::Voc() const { return voc; }

string Humanoid::VocStr() const {
  string rv;

  rv = VocRules::VocToStr(voc);

  return rv;
}

int Humanoid::Level() const { return level; }

long Humanoid::XP() const { return xp; }


vector<string> Humanoid::Pack() const {
  vector<string> rv;
 

  rv = pack->PackClass::WpnNames();

  GameSpace::Sort(rv);

  return rv;
}



Weapon* Humanoid::FindWeapon(Weapon* wpn) {
  Weapon* rv;
  Weapon* temp;
  bool help;

  if (IsActive() and wpn != NULL) {
    temp = PlayerClass::LoseWeapon();
    pack->AddWeapon(temp);
    rv = PlayerClass::FindWeapon(wpn);

  } else {
    rv = wpn;
  }

  return rv;
}


Weapon* Humanoid::ChangeWeapon(string wName) {
  Weapon* temp = NULL; 
  Weapon* rv = NULL; 

  
  
  if (IsActive() and pack->InPack(wName) and PlayerClass::HasWeapon()) 
  { 
    temp = pack->RemoveWeapon(wName);
    pack->AddWeapon(PlayerClass::LoseWeapon());
    rv = PlayerClass::FindWeapon(temp);
  } else {rv = NULL;} 

  return rv;
}



int Humanoid::RollAttack() const {
  int attack;
  VocRules* vrPtr = VocRules::GetVocRules();
  attack = 0;

  if (IsActive())

  {
    attack = Dice::Roll(Name(), ATT, 1, 20);

    if (HasWeapon()) {
      if (Weapon::IsRange(WeaponName())) {
        attack = attack + vrPtr->BaseAttackBonus(voc, level);
        attack = attack + AbilityMod(DEX);
      }

      else if (Weapon::IsMelee(WeaponName())) {
        attack = attack + vrPtr->BaseAttackBonus(voc, level);
        attack = attack + AbilityMod(STR);
      }

    }

    else if (!HasWeapon()) {
      attack = attack + AbilityMod(STR);
    }
  }

  else {
    attack = 0;
  }

  return attack;
}

int Humanoid::RollSavingThrow(SavingThrowType kindOfThrow) const {
  int save = 0;
  int bonus;
  VocRules* vrPtr = VocRules::GetVocRules();

  if (IsActive())

  {
    if (!ValidThrow(kindOfThrow)) {
      throw INVALID_SAVINGTHROW;
    }

    if (ValidThrow(kindOfThrow)) {
      save = Dice::Roll(Name(), SVTH, 1, 20);

      bonus = vrPtr->VocRules::BaseSaveBonus(voc, level, kindOfThrow) +
              WhichMod(kindOfThrow);

      save = save + bonus;
    }
  } else {
    save = 0;
  }

  if (save < 0) {
    save = 0;
  }

  return save;
}

long Humanoid::UpdateXP(int value) {
  int updatedHP;

  int xpCheck;
  int XPforPromotion;

  VocRules* vrPtr = VocRules::GetVocRules();

  if (value <= 0 or !IsActive()) {
    return xp;
  }

  if (value >= vrPtr->XPforPromotion(level + 1)) {
    while (xp + value >= vrPtr->XPforPromotion(level + 1) and
           level <= NUM_LEVELS - 1) {
      LevelUp();
      XPforPromotion = vrPtr->XPforPromotion(level + 1);
    }
  } else if (value < vrPtr->XPforPromotion(level + 1)) {
    xp = xp + value;
    return xp;
  }

  xp = xp + value;

  return xp;
}

void Humanoid::LevelUp() {
  VocRules* vocPoint;
  vocPoint = VocRules::GetVocRules();

  int hitDie = vocPoint->HitDie(voc);
  int hpAdd;
  int total;

  hpAdd = Dice::Roll(Name(), GameSpace::HP, 1, hitDie) + AbilityMod(CON);

  if (hpAdd <= 0) {
    hpAdd = 1;
    UpdateMaxHP(hpAdd);
  }

  else {
    UpdateMaxHP(hpAdd);
  }

  level++;
}

void Humanoid::Write(ostream& out) const {
  out << VocStr() << '#' << Level() << '#' << XP();
  PlayerClass::Write(out);
  out << '\t';
  out << '(';
  OutputPack(out);
  out << ')';
  out << '#'; 
  out << endl;
}

void Humanoid::OutputPack(ostream& out) const {
  vector<string> myPack;
  vector<string>::iterator iter; 

  myPack = Pack();

  for (iter = myPack.begin(); iter != myPack.end(); ++iter) {
    if (iter == myPack.end() - 1) {
      out << *iter;
    } else {
      out << *iter << ',';
    }
  }
  
  return;
}

Humanoid& Humanoid::operator=(const Humanoid& h) {
  if (*this != h) CopyHumanoid(h);
}

Humanoid::Humanoid(string name, VocRules::VocType voc, const int ABIL_ADJ[6])
    : PlayerClass::PlayerClass(name, ABIL_ADJ, true)

{
  if (voc == VocRules::NNE) {
    throw INVALID_VOC;
  }

  InitLevel();
  InitSkills();
  InitXP();
  SetHP(voc);
  pack = new PackClass(InitPackWt());
}

Humanoid::Humanoid(const Humanoid& h):pack(NULL), PlayerClass::PlayerClass(h) {
CopyHumanoid(h);
}


void Humanoid::SetHP(VocRules::VocType voc) {
  int hitDie[3];
  int hd;

  VocRules* vrPtr = VocRules::GetVocRules();
  hd = vrPtr->VocRules::HitDie(voc);

  hitDie[0] = 1;
  hitDie[1] = hd;
  hitDie[2] = AbilityMod(CON);

  PlayerClass::InitHP(hitDie);

  return;
}

void Humanoid::CopyHumanoid(const Humanoid& p) {
  delete pack; 
  pack = NULL; 
  
  xp = p.xp;
  level = p.level;
  voc = p.voc;
  pack = new PackClass::PackClass(*p.pack);
  PlayerClass::CopyPlayer(p); 
  
}


VocRules::VocType Humanoid::InitVoc(VocRules::VocType v) {
  if (v > VocRules::NUM_VOC or v < 0) {
    throw INVALID_VOC;
  }

  else {
    voc = v;
  }

  return voc;
}


void Humanoid::InitLevel() {
  level = 1;
  return;
}

void Humanoid::InitXP() {
  xp = 0;
  return;
}

void Humanoid::InitSkills() {
  for (int i = 0; i < MAX_SKILL; i++) {
    PlayerClass::AddSkill(INITIAL_SKILLS[voc][i]);
  }

  return;
}

int Humanoid::InitPackWt() const {
  int weight;

  weight = (25 + (AbilityMod(STR) * 5));

  return weight;
}
