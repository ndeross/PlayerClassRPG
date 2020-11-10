#ifndef HALF_ELF_CLASS
#define HALF_ELF_CLASS

#include "humanoid.h" 

using namespace std; 
using namespace GameSpace; 


class HalfElf: public Humanoid { 
    
public: HalfElf(string name, VocRules::VocType voc = DEFAULT_VOC);
        // Creates an elf 

        string RaceStr() const;
        // Returns ELF as a string 
        
        virtual vector<string> InitialWeaponList() const;
        // Returns the initial weapon based on the chosen vocation 
        
        virtual void Write(ostream& out) const;
        // Essentially handles just the race, then calls up to the other write functions
        
        virtual HalfElf* Clone() const;
        // Clones the elf class, used in handleclass 
        
        virtual Weapon* FindWeapon(Weapon* wpn); 
        
        virtual int RollSavingThrow(SavingThrowType kind) const;  
 
        
protected: 
        
        
private: static const string RACE; // constant string returning HALF ELF 
         static const int ABIL_ADJ[6]; // Constant array of ability mods 
         static const VocRules::VocType DEFAULT_VOC = VocRules::ROG; // Default vocation for elf 
         static const int NUM_INIT_WPN = 2; 
         static const string INIT_WEAPONS[VocRules::NUM_VOC][NUM_INIT_WPN];  // Initial Weapon List
       
         
         HalfElf(); // Default constructor, used in nothing
}; 


#endif
