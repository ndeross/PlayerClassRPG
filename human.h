#ifndef HUMAN_CLASS
#define HUMAN_CLASS

#include "humanoid.h" 

using namespace std; 
using namespace GameSpace; 


class Human:public Humanoid { 
    
public: Human(string name, VocRules::VocType voc = DEFAULT_VOC);
// Creates an Human

        string RaceStr() const; 
     // Returns HUMAN as a string 
        
        virtual vector<string> InitialWeaponList() const; 
         // Returns the initial weapon based on the chosen vocation 
        
        virtual void Write(ostream& out) const; 
        // Essentially handles just the race, then calls up to the other write functions
        
        virtual Human* Clone() const; 
        // Clones the Human class, used in handleclass 
        
private: static const string RACE;  // constant string returning RACE
         static const int ABIL_ADJ[6]; // Constant array of ability mods 
         static const VocRules::VocType DEFAULT_VOC = VocRules::FTR; // Default vocation for human
         static const string INIT_WEAPONS[VocRules::NUM_VOC]; // Initial Weapon List
       
         
         Human(); 
}; 


#endif
