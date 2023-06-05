//limitSwitchY:
//Historique: 
// 2023-04-02, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteLimitSwitchY.h"
#include "limitSwitchY.h"

//Definitions privees
//static const char* TAG = "LIMIT SWITCH Y";


//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
unsigned char limitSwitchY_litLEtat(void)
{
   return piloteLimitSwitchY_litLEntree();
}


void limitSwitchY_initialise(void)
{

}