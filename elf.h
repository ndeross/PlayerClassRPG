#ifndef ELF_CLASS
#define ELF_CLASS

#include "humanoid.h" 

using namespace std; 
using namespace GameSpace; 


class Elf:public Humanoid { 
    
public: Elf(string name, VocRules::VocType voc = DEFAULT_VOC);
        // Creates an elf 

        string RaceStr() const;
        // Returns ELF as a string 
        
        virtual vector<string> InitialWeaponList() const;
        // Returns the initial weapon based on the chosen vocation 
        
        virtual void Write(ostream& out) const;
        // Essentially handles just the race, then calls up to the other write functions
        
        virtual Elf* Clone() const;
        // Clones the elf class, used in handleclass 
        
protected:// Elf * Elf::Clone() const; 
        
        
private: static const string RACE; // constant string returning ELF 
         static const int ABIL_ADJ[6]; // Constant array of ability mods 
         static const VocRules::VocType DEFAULT_VOC = VocRules::WIZ; // Default vocation for elf 
         static const string INIT_WEAPONS[VocRules::NUM_VOC]; // Initial Weapon List
       
         
         Elf(); // Default constructor, used in nothing
}; 


#endif
