//electroaimant:
//Historique: 
// 2023-04-02, David Normandeau, creation

//INCLUSIONS
#include "main.h"
#include "piloteElectroaimant.h"
#include "electroaimant.h"

//Definitions privees
//static const char* TAG = "ELECTROAIMANT";


//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void electroaimant_active()
{
   piloteElectroaimant_metLaSortieA(ELECTROAIMANT_VALEUR_POUR_ACTIVER_AIMANT);
}

void electroaimant_eteint()
{
    piloteElectroaimant_metLaSortieA(ELECTROAIMANT_VALEUR_POUR_ETEINDRE_AIMANT);
}

void electroaimant_initialise(void)
{
    piloteElectroaimant_metLaSortieA(ELECTROAIMANT_VALEUR_POUR_ETEINDRE_AIMANT);
}
