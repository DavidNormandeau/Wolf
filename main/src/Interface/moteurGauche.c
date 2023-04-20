//moteurGauche:
//Historique: 
// 2023-04-23, David Normandeau, creation

//INCLUSIONS
#include "main.h"
#include "piloteMoteurGauche.h"
#include "moteurGauche.h"

//Definitions privees
static const char* TAG = "MOTEUR GAUCHE";


//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void moteurGauche_tourneDe(int nbreDeSteps, int vitesse)
{
    for(int i; i < nbreDeSteps; i++)
    {
        piloteMoteur1_metStepA(1);
        //delay
        piloteMoteur1_metStepA(0);
        //delay
    }
}

void moteurGauche_setLaDirection(direction_t direction)
{
    piloteMoteur1_metDirA(direction);
}

void moteurGauche_initialise(void)
{
   
}
