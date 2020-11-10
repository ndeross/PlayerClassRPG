#ifndef ORC_CLASS
#define ORC_CLASS

#include "humanoid.h" 

using namespace std; 
using namespace GameSpace; 


class Orc:public Humanoid { 
    
public: Orc(string name, VocRules::VocType voc = DEFAULT_VOC); 
        // Creates an ORC

        string RaceStr() const; 
        // Returns ORC as a string 
        
        virtual vector<string> InitialWeaponList() const; 
        // Returns the initial weapon based on the chosen vocation 
        
        virtual void Write(ostream& out) const; 
          // Essentially handles just the race, then calls up to the other write functions
        
         virtual Orc* Clone() const; 
          // Clones the orc class, used in handleclass 
        
private: static const string RACE; // constant string returning RACE
         static const int ABIL_ADJ[6]; // Constant array of ability mods 
         static const VocRules::VocType DEFAULT_VOC = VocRules::BBN; // Default vocation for Orc
         static const string INIT_WEAPONS[VocRules::NUM_VOC]; // Initial Weapon List
       
         
         Orc(); 
}; 


#endif
