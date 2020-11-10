// pack 

#ifndef PACK
#define PACK


#include <iostream> 
#include <vector>
#include <string>  
#include "wpn.h" 
#include "gamespace.h" 


class PackClass 
{ 
  public: 
  
    PackClass(int wt); 
    PackClass(const PackClass &p); 
    ~PackClass(); 
    
    PackClass& operator=(const PackClass& p); 
    bool AddWeapon(Weapon *w); 
    Weapon:: Weapon* RemoveWeapon(string wName); 
    void EmptyPack(); 
   
    bool InPack(string wName) const; 
    int Size() const; 
    int Wt() const; 
    int MaxWt() const; 
    bool IsEmpty() const; 
    bool IsFull() const;
    
    vector<string> WpnNames() const; 
    

    
    void Write(ostream &out) const; 
    
   
   private: 
   
   vector<Weapon *>:: iterator FindWeapon(string wName);    
   void CopyPack(const PackClass& p); 
  
   PackClass(); 
  
   int currentWeight; 
   vector <Weapon *> pack; 
   const int MAX_WT;   

   
}; 




#endif 
