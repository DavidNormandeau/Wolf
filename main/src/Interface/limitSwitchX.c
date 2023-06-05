//limitSwitchX:
//Historique: 
// 2023-04-02, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteLimitSwitchX.h"
#include "limitSwitchX.h"

//Definitions privees
//static const char* TAG = "LIMIT SWITCH X";


//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
unsigned char limitSwitchX_litLEtat(void)
{
   return piloteLimitSwitchX_litLEntree();
}


void limitSwitchX_initialise(void)
{

}
