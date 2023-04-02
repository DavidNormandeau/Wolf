#include "main.h"
#include "piloteDetectionPiece.h"
#include "piloteElectroaimant.h"
#include "piloteLimitSwitchX.h"
#include "piloteLimitSwitchY.h"
#include "piloteMoteur1.h"
#include "piloteMoteur2.h"
#include "piloteUart2.h"

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
    main_initialise();

    while(1)
    {
        printf("Hello World!");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}



void main_initialise()
{
    piloteDetectionPiece_initialise();
    piloteElectroaimant_initialise();
    piloteLimitSwitchX_initialise();
    piloteLimitSwitchY_initialise();
    piloteMoteur1_initialise();
    piloteMoteur2_initialise();
    //piloteUart2_initialise();        //incomplet
}
