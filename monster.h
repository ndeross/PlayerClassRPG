#ifndef MONSTER 
#define MONSTER

#include "player4.h" 

using namespace std; 
using namespace GameSpace; 


class Monster: public PlayerClass { 
    
public: 
    virtual vector<string> InitialWeaponList() const = 0; 
    virtual void Write(ostream& out) const; 
     virtual Monster* Clone() const = 0; 
    
     
protected: 
    Monster(string name, const int abilAdj[], const int hitDie[]); 
    virtual int RollAttack(const int AttackBonus[]) const; 
    virtual int RollSavingThrow(SavingThrowType kindOfThrow, const int savingThrows[]) const; 
    
    
private: 
   // int AttackBonus(int[] baseAttackBonus) const; 
    Monster(); 
    
}; 

#endif
