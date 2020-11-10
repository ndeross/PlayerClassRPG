// pack  
 
#include "pack.h" 


 
PackClass:: PackClass(): MAX_WT(0) 
{
} 
 


PackClass::PackClass(int wt): MAX_WT(wt) 
{


if (MAX_WT < 0) throw INVALID_MISC; 
currentWeight = 0; 

}

 
PackClass::PackClass(const PackClass &p): MAX_WT(p.MAX_WT) { 

  if (this != &p) 
  CopyPack(p); 

} 

 
PackClass::~PackClass(){ 
EmptyPack(); 
}  


vector<string> PackClass:: WpnNames() const { 
vector<string> rv;
string value; 

for (int i = 0; i < pack.size(); i++) 
{ value = pack[i]->NameAndNum();
  rv.push_back(value); 
}

return rv; 

} 
    
PackClass& PackClass::operator=(const PackClass& p){

if (this != &p) 
CopyPack(p); 
} 


bool PackClass::AddWeapon(Weapon *w){
 bool isAdded = false; 
 
 if(w != NULL) { 
     if (MAX_WT >= currentWeight + w->Wt()) { 
       pack.push_back(w); 
       isAdded = true; 
       currentWeight += w->Wt(); 
     }
 }else {isAdded = false;} 

return isAdded; 

}
 

Weapon* PackClass::RemoveWeapon(string wName){
 
vector<Weapon*>:: iterator iter = FindWeapon(wName); 
Weapon* rv = NULL; 

if (iter != pack.end()) 
{ 
    rv = *iter; 
    pack.erase(iter); 
    
} 

return rv; 

}
 

 
void PackClass::EmptyPack() { 

 for (int i = 0; i < pack.size(); i++) 
 { delete pack[i]; 
   pack[i] = NULL; 
 }
 
 pack.clear();  
}  
 
 
 
bool PackClass:: InPack(string wName) const{

bool rv = false;  

for (int i =0; i < pack.size(); i++) { 

if (Ucase(pack[i]->Name()) == Ucase(wName)) { rv = true; } 

} 

return rv; 
 
} 



 
int PackClass:: Size() const {

return pack.size(); 

} 



 
int PackClass:: Wt() const{

return currentWeight; 

} 



 
int PackClass:: MaxWt() const {

return MAX_WT; 

} 

 
bool PackClass:: IsEmpty() const { 

return (pack.size() == 0); 

} 
   
bool PackClass:: IsFull() const { 

return (currentWeight == MAX_WT); 


}  

   
void PackClass:: Write(ostream &out) const{

for (int i = 0; i < pack.size(); i++) {
out << pack[i]->Name() << endl; 
}
} 
    
   
void PackClass::CopyPack(const PackClass& p) { 

 EmptyPack(); 
 *const_cast<int*> (&MAX_WT) = p.MAX_WT; 
 
 
 for (int i = 0; i < p.pack.size(); i++) 
  { 
 if (p.pack[i] != NULL)
  pack.push_back(new Weapon(*p.pack[i]));   
  } 

return; 
}




vector<Weapon *> :: iterator PackClass:: FindWeapon(string wName){ 

vector<Weapon *> :: iterator rv = pack.end(); 
vector<Weapon *> :: iterator iter; 
Weapon *aWep;
bool found = false;    

for (iter = pack.begin(); iter !=pack.end() and !found; ++iter) { 

aWep = *iter;  

if (Ucase(aWep->Name()) == Ucase(wName)) { rv = iter; } 


} 

return rv; 

}











   
   
   
   

 
