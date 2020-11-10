#include "elf.h" 

using namespace std; 
using namespace GameSpace; 

const string Elf::RACE = "ELF";
const int Elf::ABIL_ADJ[6] = {2, -2, 0, 0, 0, 0};
const string Elf::INIT_WEAPONS[VocRules::NUM_VOC] = {
    "DAGGER", "LONG SWORD", "SWORD", "RAPIER", "SHORT BOW"};


Elf::Elf(string name, VocRules::VocType voc):Humanoid(name, Humanoid::InitVoc(voc), ABIL_ADJ) {
    
}




string Elf::RaceStr() const { return RACE; }




vector<string> Elf::InitialWeaponList() const {
  vector<string> init;


    init.push_back(Elf::INIT_WEAPONS[Humanoid::Voc()]);

  return init;
}



void Elf::Write(ostream& out) const {
    
    out << RaceStr() << '#'; 
    Humanoid:: Write(out); 
    
}


Elf* Elf:: Clone() const { 
    return new Elf(*this); 
}

Elf::Elf():Humanoid("DEFAULT", VocRules:: NNE, ABIL_ADJ) {}
