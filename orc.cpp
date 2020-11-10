#include "orc.h" 

using namespace std; 
using namespace GameSpace; 

const string Orc::RACE = "ORC";
const int Orc::ABIL_ADJ[6] = {0, 0, -2, -2, 2, -1};
const string Orc::INIT_WEAPONS[VocRules::NUM_VOC] = {
    "DAGGER", "CROSSBOW", "SWORD", "SHORT BOW", "LIGHT CROSSBOW"};


Orc::Orc(string name, VocRules::VocType voc):Humanoid(name, Humanoid::InitVoc(voc), ABIL_ADJ) {
    
}




string Orc::RaceStr() const { return RACE; }




vector<string> Orc::InitialWeaponList() const {
  vector<string> init;

 
init.push_back(Orc::INIT_WEAPONS[Humanoid:: Voc()]);

  return init;
}

Orc* Orc:: Clone() const { 
    return new Orc(*this); 
}


void Orc::Write(ostream& out) const {
    
    out << RaceStr() << '#'; 
    Humanoid:: Write(out); 
    
}



Orc::Orc():Humanoid("DEFAULT", VocRules:: NNE, ABIL_ADJ) {}
