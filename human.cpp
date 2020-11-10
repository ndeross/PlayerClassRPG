#include "human.h" 

using namespace std; 
using namespace GameSpace; 

const string Human::RACE = "HUMAN";
const int Human::ABIL_ADJ[6] = {0, 0, 0, 0, 0, 0};
const string Human::INIT_WEAPONS[VocRules::NUM_VOC] = {
    "DAGGER", "CROSSBOW", "RAPIER", "SWORD", "CLUB"};


Human::Human(string name, VocRules::VocType voc):Humanoid(name, Humanoid::InitVoc(voc), ABIL_ADJ) {
    
}

Human* Human:: Clone() const { 
    return new Human(*this); 
}


string Human::RaceStr() const { return RACE; }




vector<string> Human::InitialWeaponList() const {
  vector<string> init;


    init.push_back(Human::INIT_WEAPONS[Humanoid::Voc()]);

  return init;
}



void Human::Write(ostream& out) const {
    
    out << RaceStr() << '#'; 
    Humanoid:: Write(out); 
    
}



Human::Human():Humanoid("DEFAULT", VocRules:: NNE, ABIL_ADJ) {}
