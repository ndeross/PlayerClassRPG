//Nicholas DeRoss

#ifndef PLAYER
#define PLAYER


#include <iostream>
#include <string> 
#include "gamespace.h"
#include "voc.h"  
 
using namespace std;
using namespace GameSpace; 


class PlayerClass {

                  // Enumerated type representing the players race, mapped to int 
        public:   enum  RaceType {HUMAN=0, ELF, ORC, TROLL, OGRE};
        
        
                  // Enumerated type representing the players ability 
                                   
                  enum AbilityType {DEX=0, CON, INT, CHAR, STR, WIS};
        
                       
                   static const string DEFAULT_NAME; // Default name is "Default" 
                   static const RaceType DEFAULT_RACE; // Default Race is "HUMAN" 
                   static const int DEAD; // Dead = -10 
                   static const int DYING; // Dying = -1                                                       
                   static const int DISABLED; // Disabled = 0
                   static const int NUM_RACES = 5; // Number of races represented in the game 
                   static const int NUM_HUMANOIDS = 3; // Number of human like races represented in game 
                   static const int NUM_MONSTERS = 2;  // Number of monster types represented in game 
                   static const string RACE_STR[NUM_RACES]; // An array filled with the RaceTypes represented as strings 
                   static const int NUM_ABILITIES = 6; // The amount of abilities represented in the game
                   static const int NUM_LEVELS = 20;   // Ammount of levels possible 
                   static const int MAX_ROWS = 10;  // Maximum number of rows allowed on board 
                   static const int MAX_COLS = 10;  // Maximum number of columns allowed on board
                   static const VocRules:: VocType DEFAULT_VOC[NUM_RACES]; // Default vocations of each race                                                                        
                   static const int VOC_DICE = 3; // Number of dice to throw in ability roll
                   static const int VOC_FACES = 6; // Number of faces on the abilitiy dice
                   
                   static const int TROLL_HIT_DICE = 6; //Number of dice thrown in troll's hp throw  
                   static const int TROLL_HIT_FACES = 8; //number of faces on the dice 
                   
                   static const int OGRE_HIT_DICE = 4; //Number of dice thrown in ogre HP roll 
                   static const int OGRE_HIT_FACES = 8; //number of faces on the dice 
                   
                    
                  /* Narrative: Creates a default instance of the player class, with name default, race human, and vocation fighter 
                     Pre-Conditions:NNE 
                     Post-Conditions:Player instance created 
                  */ 
                  PlayerClass(); 
                  
                  
                  
                  /* Narrative: Creates a default player class with the name specified in the parameter 
                     Pre-Conditions: NNE
                     Post-Conditions: Instance of player class created 
                  */ 
                  
                  PlayerClass(string newName); 
                  
                  
                  
                  /* Narrative: Creates a player class with a specified name and race
                     Pre-Conditions:NNE 
                     Post-Conditions:PlayerClass created with specified name and race
                  */ 
                  PlayerClass(string n, RaceType r);
                  
                  
                  
                  
                  /* Narrative: Creates a player class with specified name, race, and vocation type
                     Pre-Conditions:NNE 
                     Post-Conditions:PlayerClass created 
                  */ 
                  PlayerClass(string n, RaceType r, VocRules:: VocType v); 
                
                
                
                  /* Narrative: Observer function that reports the name of the player 
                     Pre-Conditions:NNE
                     Post-Conditions:Name returned 
                  */ 
                  string Name() const; 
                
                
                  
                  /* Narrative: Observer function that reports the players race
                     Pre-Conditions:NNE 
                     Post-Conditions: Race returned 
                  */ 
                  int Race() const; 
                
                
                  
                  /* Narrative:Observer function that reports the XP 
                     Pre-Conditions: NNE 
                     Post-Conditions: XP Reported 
                  */ 
                  long XP()const; 
                
                
                  
                  /* Narrative: The players specific ability is returned as an int value 
                     Pre-Conditions: PlayerClass exists 
                     Post-Conditions:Specified ability in parameter returned
                  */ 
                  
                  int Ability(AbilityType ability); 
                
                
                  
                  /* Narrative:A string representing the players race is returned
                     Pre-Conditions: Race exists 
                     Post-Conditions:Race string returned 
                  */ 
                  string RaceStr()const; 
                
                
                  
                  /* Narrative: A boolean function set to true if the player is a humanoid race
                     Pre-Conditions:Player has set race 
                     Post-Conditions: True or false returned 
                  */ 
                  
                  bool IsHumanoid()const; 
                
                
                  
                  /* Narrative:Observer that returns the players vocation as a VocType
                     Pre-Conditions:Player has set Voc type 
                     Post-Conditions: Voc returned 
                  */ 
                  
                  VocRules::VocType Voc() const; 
                
                
                  
                  /* Narrative: A boolean function set to true if the player is a monster race
                     Pre-Conditions: NNE  
                     Post-Conditions:True or false returned 
                  */ 
                  
                  bool IsMonster()const; 
                
                
                  
                  /* Narrative:Function that returns the players vocation as a string value
                     Pre-Conditions:NNE
                     Post-Conditions:Vocation string returned
                  */ 
                  
                  string VocStr()const; 
                
                
                  
                  /* Narrative: Function that returns positive if the player's HP is at or below the "dead" threshold 
                     Pre-Conditions: Players HP is set to a certain value
                     Post-Conditions: True/False returned
                  */ 
                  
                  bool IsDead()const; 
               
               
                  
                  /* Narrative: Observer that returns the postion of the player on the Row of the board 
                     Pre-Conditions:NNE 
                     Post-Conditions:Row returned 
                  */ 
                  int Row()const; 
                  
               
               
                  /* Narrative:Function that returns positive if the player's HP is at or below the "dying" threshold
                     Pre-Conditions:Players HP set to a certain value
                     Post-Conditions:True/False returned
                  */ 
                  bool IsDying()const;
               
               
                  
                  /* Narrative: Observer that returns the postion of the player on the column of the board 
                     Pre-Conditions:NNE 
                     Post-Conditions:Column returned 
                  */ 
                  int Col()const; 
               
               
                  
                  /* Narrative:Function that returns positive if the player's HP is at or below the "dying" threshold
                     Pre-Conditions:Players HP set to a certain value
                     Post-Conditions:True/False returned 
                  */ 
                  bool IsDisabled()const; 
               
               
                  
                  /* Narrative: Observer function that will return the players current level 
                     Pre-Conditions:NNE
                     Post-Conditions:Level returned 
                  */ 
                  int Level()const; 
               
               
                  
                  /* Narrative:Calculates the players ability modifier based on the parameter ability specified 
                     Pre-Conditions:Player has set abilities 
                     Post-Conditions:Ability modifier returned 
                  */ 
                  int AbilityMod(AbilityType ability);
               
               
                  
                  /* Narrative: Observer that returns the players current HP 
                     Pre-Conditions:NNE 
                     Post-Conditions:HP returned 
                  */ 
                  int HP()const;
               
               
                  
                  /* Narrative:Observer that returns the players Max HP 
                     Pre-Conditions:NNE 
                     Post-Conditions:Max HP returned 
                  */ 
                  int MaxHP()const;  
               
               
                  
                  /* Narrative: Function that allows the player to change positions on the board as long as they 
                                are within the specified board parameters  
                     Pre-Conditions: The player has a set location (row, column); 
                     Post-Conditions:If data is allowed, players location is changed 
                  */ 
                  bool SetCell(int newRow, int newCol);
               
               
                  
                  /* Narrative: Checks the location of the inputed position in "SetCell" to verify it's availabilty 
                     Pre-Conditions: The function "set cell" has been entered
                     Post-Conditions: True/False returned 
                  */ 
                  bool Check (int newRow, int newCol); 
               
               
                  
                  /* Narrative: Updates the players current HP, cannot go past the players Max HP 
                     Pre-Conditions:NNE 
                     Post-Conditions:Players HP is updated 
                  */ 
                  int UpdateHP(int modification); 
               
               
                  
                  /* Narrative: Updates the players XP, sometimes triggering a level up
                     Pre-Conditions:NNE 
                     Post-Conditions:Updated XP returned 
                  */ 
                  long UpdateXP(int value);
               
               
               
                  
                  /* Narrative:The players hit die, the die used in rolls for HP, is set 
                     Pre-Conditions:NNE 
                     Post-Conditions:Hit die returned 
                  */ 
                  int SetHitDie();
               
               
                  
                  /* Narrative: Sets all the abilities of the player via dice rolls, taking in account their race ability
                                   modifiers   
                     Pre-Conditions:NNE
                     Post-Conditions:Abilities set 
                  */ 
                  void SetAbilities(RaceType race);
               
               
                  
                  /* Narrative: Writes the player out in the specified format 
                     Pre-Conditions:NNE
                     Post-Conditions:Outputs the player in the specified format 
                  */ 
                  void Write(ostream& out)const;
               
               
                  
                  /* Narrative: This function was abandoned 
                     Pre-Conditions:
                     Post-Conditions:
                  */ 
                  void OutputAbil()const;
               
               
                  
                  /* Narrative:Sets the inital Max HP of the player based on a dice roll 
                     Pre-Conditions:NNE
                     Post-Conditions:HP set 
                  */ 
                  void SetHP();
               
               
                  
                  /* Narrative: Sets the stats of the player not stored in the ability array(postition on board, initial XP, etc.) 
                     Pre-Conditions:NNE 
                     Post-Conditions:Stats are set 
                  */ 
                  void SetStats();
              
              
                  
                  /* Narrative: The name of the player is validated and set, and stripped of white space,
                                 if invalid it is set to the default name 
                     Pre-Conditions:NNE
                     Post-Conditions:Name is set 
                  */ 
                  void SetName(string n);
              
              
                  
                  /* Narrative:The race of the player is validated and set, if invalid, it is set to human
                     Pre-Conditions:NNE 
                     Post-Conditions: The race of the player is set 
                  */ 
                  void SetRace(RaceType r);
              
              
                  
                  /* Narrative: Sets the monster player type's  abilities and statistics 
                     Pre-Conditions:NNE
                     Post-Conditions:Abilities and stats set 
                  */ 
                  void SetMonsterStats();
              
              
                  
                  /* Narrative:Vocation of the player is validated and set, if invalid it is set to 
                                  the default race stored in the default race array 
                     Pre-Conditions:NNE
                     Post-Conditions:Race set 
                  */ 
                  void SetVoc(VocRules:: VocType v);
              
              
                  
                  /* Narrative: The player increases in XP enough to trigger a level up, new max HP set, current HP set
                                      to Max HP 
                     Pre-Conditions:The player gained enough XP to level up 
                     Post-Conditions:The player increases in level 
                  */ 
                  void LevelUp();  
              
              
                  
                  /* Narrative:Checks to see if the player is able to level up, and isn't dying, dead, or disabled 
                     Pre-Conditions:The player has a set HP 
                     Post-Conditions:True/False returned based on if conditions are met 
                  */ 
                  bool CanLevel();
              
              
                  
                  /* Narrative:A monster PlayerType's stats are set (position on board, inital level, initialXP) 
                     Pre-Conditions:NNE
                     Post-Conditions:Monsters stats are set 
                  */ 
                  void SetStatsM(); 
              
              
                  
                  /* Narrative:Overloaded assignment operator used to compare two player classes based on their name 
                  */ 
                  
                  bool operator== (const PlayerClass& p);
              
              
                  // Narrative: Overloaded assignment operator used to compare two player classes based on their name
                  bool operator!= (const PlayerClass& p); 

                
         private:  
                  string name; // Name of player
                  RaceType race; // Race of player 
                  int row; // Position on row of board of player 
                  int col; // Position on col of board of player 
       VocRules:: VocType voc; // Vocation of player 
                  int vocLevel; // Level of vocation of player 
                  int level; // Experience level of player 
                  long xp; // Ammount of experience of player 
                  int maxHP; // Maximum xp player can 
                  int currentHP; // Current hit points the player has 
                  int hitDie; // Hit die used by player during game 
                  static const int AB_ADJ[NUM_RACES][NUM_ABILITIES];// two dimensional array of ability adjustments based on                                                                                                                
                  //                                                     players Race
                  
                   int Abilities[NUM_ABILITIES];       // Array representing the abilities the player possess      
}; 
 
// Overloaded assignment operator that is essentially just a call to the Write function, overloads << 

ostream& operator<<(ostream& out, const PlayerClass& c); 

#endif                
