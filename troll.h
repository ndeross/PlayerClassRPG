#ifndef TROLL
#define TROLL


#include "monster.h" 

using namespace std; 
using namespace GameSpace; 


class Troll: public Monster { 

    
public: 
    
    Troll(string name); 
    
    virtual string RaceStr() const; // returns race string 
    
    virtual vector<string> InitialWeaponList() const;  // inital weapon 
    
    virtual int RollAttack() const; // rolls attack  
    
    virtual int RollSavingThrow(SavingThrowType kind) const; 
      // rolls the saving throw 
    
    virtual void Write(ostream &out) const; 
    // writes troll attributes 
    
    
    virtual Troll* Clone() const;
    // clones the troll 
    
    
private: 
    
    static const string RACE; 
    static const int ABIL_ADJ[6]; // ability adjustments
    static const int HIT_DICE[3]; // hit dice(constant for monsters) 
    static const int SAVE_THROW[3]; // constant saving throw values 
    static const int BASE_ATTACK_BONUS[2]; 
    static const string INITIAL_WPN;
    static const int NUM_INIT_WPN = 1;
    static const int NUM_INIT_SKILLS = 2; 
    static const string INIT_SKILLS[NUM_INIT_SKILLS]; // initial monster skills 
    
    
    Troll(); 
    void InitSkills(); // initializes monster skills 
}; 

#endif 
