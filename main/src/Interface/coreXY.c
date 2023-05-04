//coreXY:
//Historique: 
// 2023-04-23, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteMoteurGauche.h"
#include "piloteMoteurDroit.h"
#include "coreXY.h"

//Definitions privees
//static const char* TAG = "CORE_XY";

#define TOURNE_A_GAUCHE 0
#define TOURNE_A_DROITE 1


//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void coreXY_deplaceEnNombreDeSteps(int nbreDeSteps, direction_t direction, int vitesse)
{
    //direction
    if(direction == A1_TO_H8 || direction == _1_TO_8 || direction == H_TO_A)
    {
        piloteMoteurGauche_metDirA(TOURNE_A_DROITE);
    }
    else
    {
        piloteMoteurGauche_metDirA(TOURNE_A_GAUCHE);
    }
    if(direction == A1_TO_H8 || direction == _1_TO_8 || direction == A_TO_H)
    {
        piloteMoteurDroit_metDirA(TOURNE_A_DROITE);
    }
    else
    {
        piloteMoteurDroit_metDirA(TOURNE_A_GAUCHE);
    }

    //steps
    //Peut-être un flag pour l'arreter en cours de mouvement?????????????????
    for(int i = 0; i < nbreDeSteps; i++)
    {
        if(direction == H1_TO_A8 || direction == A8_TO_H1)
        {
            piloteMoteurGauche_metStepA(1);  
        }
        else
        {
            piloteMoteurGauche_metStepA(0); 
        } 

        if(direction == A1_TO_H8 || direction == H8_TO_A1)
        {
            piloteMoteurDroit_metStepA(1);  
        }
        else
        {
            piloteMoteurDroit_metStepA(0); 
        }
        
        vTaskDelay(pdMS_TO_TICKS(vitesse));
        piloteMoteurGauche_metStepA(0);
        piloteMoteurDroit_metStepA(0); 
        vTaskDelay(pdMS_TO_TICKS(vitesse));
    }
}


void coreXY_initialise(void)
{
    piloteMoteurGauche_metStepA(0);
    piloteMoteurDroit_metStepA(0);
}
