#include "halfelf.h" 

using namespace std; 
using namespace GameSpace; 

const string HalfElf::RACE = "HALFELF";

const int HalfElf:: NUM_INIT_WPN; 

const int HalfElf::ABIL_ADJ[6] = {0, 0, 1, 2, 0, 1};

const string HalfElf::INIT_WEAPONS[VocRules::NUM_VOC][NUM_INIT_WPN] = {
    {"",""},  {"DAGGER", "SHORT BOW"},{"LONG SWORD", ""}, {"SWORD", ""}, {"RAPIER", "SHORT BOW"}, {"CLUB", "LIGHT CROSSBOW"} 
    };


HalfElf::HalfElf(string name, VocRules::VocType voc):Humanoid(name, Humanoid::InitVoc(voc), ABIL_ADJ) {
    
    PlayerClass::AddSkill("MOVE SILENTLY"); 
    
}


Weapon* HalfElf::FindWeapon(Weapon* wpn) {
 Weapon* rv; 
    
    if ( wpn != NULL and wpn->Wt() <= 10) {
     rv = Humanoid::FindWeapon(wpn);    
    } else {rv = wpn;};
    
    return rv; 
}


string HalfElf::RaceStr() const { return RACE; }




vector<string> HalfElf::InitialWeaponList() const {
  vector<string> init;
  
  
  for(int i = 0; i < NUM_INIT_WPN; i++) 
  { 
      string wpn = INIT_WEAPONS[Humanoid::Voc()][i]; 
      
      if (wpn != "")
      {  init.push_back(wpn); } 
  }
  
  return init; 

}



int HalfElf:: RollSavingThrow(SavingThrowType kind) const {
    
 int thrw; 
 
 thrw = Humanoid::RollSavingThrow(kind) * 1.5;  
 return thrw; 


} 


void HalfElf::Write(ostream& out) const {
    
    out << RaceStr() << '#'; 
    Humanoid:: Write(out); 
    
}


HalfElf* HalfElf:: Clone() const { 
    return new HalfElf(*this); 
}

HalfElf::HalfElf():Humanoid("DEFAULT", VocRules:: NNE, ABIL_ADJ) {}
