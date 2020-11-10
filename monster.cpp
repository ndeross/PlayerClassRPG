#include "monster.h"

using namespace std;
using namespace GameSpace;

Monster::Monster(string name, const int ABIL_ADJ[6], const int HitDie[])
    : PlayerClass::PlayerClass(name, ABIL_ADJ, false) {
  PlayerClass::InitHP(HitDie);
}

void Monster::Write(ostream &out) const { PlayerClass::Write(out); }

int Monster::RollAttack(const int AttackBonus[]) const {
  int attack;

  if (IsActive())

  {
    attack = Dice::Roll(Name(), ATT, 1, 20);

    if (HasWeapon()) {
      if (Weapon::IsRange(WeaponName())) {
        attack += AttackBonus[0];
        attack += AbilityMod(DEX);
      }

      else if (Weapon::IsMelee(WeaponName())) {
        attack = attack + AttackBonus[1];
        attack += AbilityMod(STR);
      }

    }

    else if (!HasWeapon()) {
      attack = attack + AttackBonus[1] + AbilityMod(STR);
    }
  }

  else {
    attack = 0;
  }

  return attack;
}

int Monster::RollSavingThrow(SavingThrowType kindOfThrow,
                             const int savingThrows[]) const {
  int save;
  int bonus;
  int mod;
  int rv;

  if (IsActive())

  {
    if (!ValidThrow(kindOfThrow)) {
      throw INVALID_SAVINGTHROW;
    }

    else {
      save = Dice::Roll(Name(), SVTH, 1, 20);
      bonus = savingThrows[kindOfThrow - 1];
      mod = WhichMod(kindOfThrow);
      rv = (save + mod + bonus);
    }

  }

  else {
    rv = 0;
  }

  return rv;
}
