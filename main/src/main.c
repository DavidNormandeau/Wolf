#include "main.h"
#include "piloteDetectionPiece.h"
#include "piloteElectroaimant.h"
#include "piloteLimitSwitchX.h"
#include "piloteLimitSwitchY.h"
#include "piloteMoteurGauche.h"
#include "piloteMoteurDroit.h"
#include "piloteUart2.h"
#include "detectionPiece.h"

//Definitions privees
//  static const char* TAG = "MAIN";

//Declarations de fonctions privees:
void main_initialise();

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees


void app_main(void)
{
    unsigned char echiquier[64];

    main_initialise();

    while(1)
    {
        printf("Hello World!");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        detectionPiece_litLEchiquier(echiquier);
    }
}



void main_initialise()
{
    piloteDetectionPiece_initialise();
    piloteElectroaimant_initialise();
    piloteLimitSwitchX_initialise();
    piloteLimitSwitchY_initialise();
    piloteMoteurGauche_initialise();
    piloteMoteurDroit_initialise();
    //piloteUart2_initialise();        //incomplet
    detectionPiece_initialise();
}
