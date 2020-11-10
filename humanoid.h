#ifndef HUMANOID_CLASS
#define HUMANOID_CLASS


#include "player4.h"
#include "pack.h"


using namespace std; 
using namespace GameSpace; 


class Humanoid: public PlayerClass { 
    
public:
    // DESTRUCTOR
    virtual ~Humanoid(); 
    
    VocRules::VocType Voc() const; 
    // returns the players vocation as a voc type 
    
    
    string VocStr() const;
    // returns the vocation as a string 
    
    
    int Level() const;
    // returns level as an int 
    
    long XP() const; 
    // returns the XP as a long 
 
    virtual Humanoid* Clone() const = 0;
    // no implimentation 
    
    virtual vector<string> InitialWeaponList() const = 0;  
    
    vector<string> Pack() const; 
    // returns the pack as a vector of strings 
    
    
   virtual Weapon* FindWeapon(Weapon* wpn);
    // Finds the weapon with pack specific requirments 
    
    Weapon* ChangeWeapon(string wName); 
    // changes the players weapon from the pack
    
    int RollAttack() const; 
    // roles attack 
    
    virtual int RollSavingThrow(SavingThrowType kind) const;
    // rolls saving throw 
    
    long UpdateXP(int value); 
    // updates xp 
    
    void Write(ostream& out) const; 
    // writes human specific output 
    
    // ASSIGNMENT OP
    Humanoid& operator=(const Humanoid& h); 
    
protected: 
    
    Humanoid(string name, VocRules::VocType voc,  
              const int AbilAdj[6]);
    // creates and initializes humanoid specific atributes 
    
    Humanoid(const Humanoid& h);
    // copy constructor 
    
    void CopyHumanoid(const Humanoid& h);
    // copy constructor 
    
    int HitDie() const;
    // returns hit die roll 
    
    int GetHP(); 
    // gets the HP 
    
    
    VocRules:: VocType InitVoc(VocRules::VocType v);
    
    void SetHP(VocRules::VocType voc);
    
    void LevelUp(); 
    
private: 
    
    VocRules:: VocType voc; 
    int level; 
    long xp; 
    PackClass::PackClass* pack;
    
    static const int MAX_SKILL = 3; 
    static const int NUM_LEVELS = 20; 
    static const string INITIAL_SKILLS[VocRules:: NUM_VOC][MAX_SKILL]; 
    
    
    
    void InitLevel(); // level helper function 
    void InitXP(); 
    void InitHP(); 
    void InitSkills(); 
    int InitPackWt () const; // preforms pack weight equation 
    void OutputPack(ostream& out) const; 
    
}; 

#endif 
