//Nicholas DeRoss

#ifndef PLAYER
#define PLAYER


#include <iostream>
#include <string>
#include <vector> 
#include <map> 
#include <utility>
#include "gamespace.h"
#include "voc.h" 
#include "wpn.h"


 
using namespace std;
using namespace GameSpace; 



class PlayerClass {  
    
public: 
      
    
        enum AbilityType {DEX=0, CON, INT, CHAR, STR, WIS};
        
    
        static const int NUM_ABILITIES = 6;
    
        static bool mapLoaded; 
        
        typedef map<string, AbilityType> MapType;
        
        
        virtual ~PlayerClass(); 
        
        string Name() const; 
        // Returns the name of the character
    	// pre: none  
    	// post: returns name 
        
        
        int Row() const;
        // returns the row
    	// pre: none
    	// post: returns the row
        
    
        int Col() const; 
        // returns the column
    	// pre: none
    	// post: returns the column
        
        
        int HP() const; 
        // Returns the HP (hit points)
    	// pre:  none
    	// post: returns the HP 
        
        
        int MaxHP() const; 
        
        
        int Ability(AbilityType abil) const; 
        // Returns the ability requested
    	// pre:  none.
    	// post: returns the ability value
        
        vector<int> Abilities() const; 
       	// Returns the abilities
    	// pre:  none.
    	// post: returns the abilities
        
        int AbilityMod(AbilityType abil) const; 
        // Returns the abilityMod requested
    	// pre:  none.
    	// post: returns the abilityMod value
        
        
        string WeaponName() const;
        // Returns the current wpn name, empty string if non exists
    	// pre:  none.
    	// post: returns the current weapon being used
        
        string WeaponNameAndNum() const; 
        // Returns the current wpn name and number, empty string if non exists
    	// pre:  none.
    	// post: returns the current weapon being used
        
        
        vector <string> Skills() const; 
        //Returns the vector of skills
        //Pre :
        //Post: Skill vector is returned
        
        
        bool IsActive() const; 
         // Returns true if player is active (not disabled)
        // Pre :
        //Post: True if hp >DISABLED
        
        
        bool IsDead() const; 
        //Returns true if player is dead, false otherwise.
        //Pre :
        //Post: True is returned if hp <= DEAD, false otherwise
        
        
        bool IsDying() const; 
         //Returns true if player is dying, false otherwise.
        //Pre :
        //Post: True is returned if DEAD<hp<DISABLED, false otherwis

        
        
        bool IsDisabled() const; 
         //Returns true if player is disabled, false otherwise.
        //Pre :
        //Post: True is returned if hp <= DISABLED, false otherwise
        
        
        bool HasWeapon() const; 
        // Returns if a player has a weapon 
    	// pre:  none.
    	// post: returns t/f
        
        static AbilityType StrToAbility(string s);
        // Returns the string abilitie
    	// pre:  none.
    	// post: returns the string abilitie
        
        
        
        
        int UpdateHP(int modification); 
        // Updates the HP given val
        
        
        bool SetCell(int newRow, int newCol); 
           //Set the current coordinates regardless of other fields.
        //coordinates are set (returns true) under following conditi
        //  newRow and newCol not negative
        //  newRow and newCol are both -1  (ex: -1,-1)
        //all other cases the function returns false.
        //Pre: It is up to the user to send valid moves based on the
        //Post: The players coordinates are modified and true is r
        //          otherwise false is returned
        
        
        int SkillCheck(string skill) const; 
        // returns skill check int 
        
        
        bool AddSkill(string skill);
        // Adds a skill to the players skill list 
        
        void Amnesia(); 
        // deletes all skill 
        
        virtual vector <string> InitialWeaponList() const = 0; 
        
        Weapon:: Weapon* LoseWeapon(); 
        // returns a weapon after player loses it 
        
        virtual Weapon:: Weapon* FindWeapon(Weapon* wpn); 
        // calls specific FindWeapon for human or monster 
        
        
        int RollInitiative() const;
        // rolls players initiative 
        
        virtual int RollAttack() const;
        // rolls attack 
        
        virtual int RollSavingThrow(SavingThrowType kind) const;
        // rolls saving throw 
        
        int RollDefense() const;
        // rolls defense 
        
        int RollDamage() const;
        // rolls damage 
        
      
        virtual string RaceStr() const = 0; 

        virtual void Write(ostream& out) const;
        // prints player specifc atributes 
        
        
        virtual PlayerClass* Clone() const = 0; 
    
        
        // COMPARISON OPERATORS 
        
        bool operator == (const PlayerClass& p)const;
        bool operator!= (const PlayerClass& p)const; 
        bool operator < (const PlayerClass& p)const; 
        bool operator <= (const PlayerClass& p)const;
        bool operator > (const PlayerClass& p)const;
        bool operator >= (const PlayerClass& p)const;
        
        
protected: 
    
    PlayerClass(string name, const int ABIL_ADJ[], bool rollAbil);
    // creates a playerclass 
    
    PlayerClass(const PlayerClass &p); 
    // copy constructor for playerclass 
    
    void CopyPlayer(const PlayerClass &p); 
    // does actual copying 
    
    void InitSkills(vector<string> skills);
    // initializes the players skills 
    
    void InitAbilities(const int ABIL_ADJ[NUM_ABILITIES], bool roll);
    // initializes the players abilities 
    
    void InitMonsterAbilities(const int ABIL_ADJ[NUM_ABILITIES]); 
    // initializes the monsters abilities 
    
    int RollHitDie(int numRolls, int faces, int mod) const; 
    // Rolls the players hit die 
    
    bool operator=(const PlayerClass& p); 
    // assigment operator 
    
     void OutputSkills(ostream& out) const;
     // outputs the players skills 
     
     
     void InitHP(const int HIT_DIE[3]); 
     // initializes player HP 
     
     
    bool ValidThrow(SavingThrowType kindOfThrow) const;
    // checks for valid skill throw 
    
    int WhichMod(SavingThrowType kindOfThrow) const; 
    // checks which ability mod to return
    
    Weapon* CurrentWeapon() const; 
    // returns the players current weapon 
    
    
     void UpdateMaxHP(int value); 
     // updates a players MaxHP 
     
    
private: 
    
    static const int DISABLED = 0; 
    static const int DYING = -1; 
    static const int DEAD = -10; 
    static const int MAX_NAME_SIZE = 10; 
    static const int MAX_ROWS = 10; 
    static const int MAX_COLS = 10; 
    static const int DEFAULT_DICE = 1; 
    static const int DEFAULT_FACES = 20; 
    static const int VOC_DICE = 3; 
    static const int VOC_FACES = 6;
    static const int DEFENSE_ADJ = 10;
    
    static MapType skillMap; 
    
    const string NAME; 
    int row; 
    int col; 
    int currentHP; 
    int maxHP;
    int Abil[NUM_ABILITIES]; 
    Weapon:: Weapon* weapon; 
    vector<string> mySkills; 
    
    static MapType LoadSkillTable(); 
    // loads the main games skills table 
    
    
    PlayerClass(); 
    
    string InitName(string n); 
    // initializes the players name 
     
    int WhichMod(SavingThrowType kindOfThrow);
    
    
    bool CheckCell (int newRow, int newCol);
    // checks for valid cell in set cell 
    
    bool ValidSkill(string skill) const;
    // checks to see if the skill being added is valid 
    
    
    void SetHitDie(); 
    // abandoned 
    
}; 

ostream& operator<<(ostream& out, const PlayerClass* p); 


#endif
