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
    if(direction == A8_TO_H1 || direction == _8_TO_1 || direction == A_TO_H)
    {
        piloteMoteurGauche_metDirA(TOURNE_A_GAUCHE);
    }
    else
    {
        piloteMoteurGauche_metDirA(TOURNE_A_DROITE);
    }
    if(direction == H8_TO_A1 || direction == _8_TO_1 || direction == H_TO_A)
    {
        piloteMoteurDroit_metDirA(TOURNE_A_GAUCHE);
    }
    else
    {
        piloteMoteurDroit_metDirA(TOURNE_A_DROITE);
    }

    piloteMoteurDroit_enable(); //Enable les 2 moteurs

    //steps
    for(int i = 0; i < nbreDeSteps; i++)
    {
        if(direction == A1_TO_H8 || direction == H8_TO_A1)
        {
            piloteMoteurGauche_metStepA(0);  
        }
        else
        {
            piloteMoteurGauche_metStepA(1); 
        } 
        if(direction == H1_TO_A8 || direction == A8_TO_H1)
        
        {
            piloteMoteurDroit_metStepA(0);  
        }
        else
        {
            piloteMoteurDroit_metStepA(1); 
        }
        
        vTaskDelay(pdMS_TO_TICKS(vitesse));
        piloteMoteurGauche_metStepA(0);
        piloteMoteurDroit_metStepA(0); 
        vTaskDelay(pdMS_TO_TICKS(vitesse));
    }

    piloteMoteurDroit_disable();    //Disable les 2 moteurs
}


void coreXY_initialise(void)
{
    piloteMoteurGauche_metStepA(0);
    piloteMoteurDroit_metStepA(0);
    piloteMoteurDroit_disable();        
}
