#include "define.h"
#include "piloteDetectionPiece.h"
#include "piloteElectroaimant.h"
#include "piloteLimitSwitchX.h"
#include "piloteLimitSwitchY.h"
#include "piloteMoteurGauche.h"
#include "piloteMoteurDroit.h"
#include "piloteUart2.h"
#include "detectionPiece.h"
#include "coreXY.h"
#include "electroaimant.h"
#include "limitSwitchX.h"
#include "limitSwitchY.h"
#include "taskCalibration.h"
#include "taskDeplacementPiece.h"
#include "taskGestionControleur1.h"
#include "taskRxUart.h"
#include "taskTxUart.h"

//Definitions privees
//  static const char* TAG = "MAIN";

//Declarations de fonctions privees:
void main_initialise();

//Definitions de variables publiques:
//pas de variables publiques


//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void app_main(void)
{
    main_initialise();

    //TEST
    gpio_config_t conf = {
        .pin_bit_mask = (1ULL<<GPIO_NUM_13),               
        .mode = GPIO_MODE_OUTPUT,                  
        .pull_up_en = GPIO_PULLUP_DISABLE,          
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       
        .intr_type = GPIO_INTR_DISABLE 
    };
    gpio_config(&conf);
    gpio_set_level(GPIO_NUM_13, 1);
    

    while(1)
    {
        gpio_set_level(GPIO_NUM_13, 1);
        vTaskDelay(500/portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_13, 0);
        vTaskDelay(500/portTICK_PERIOD_MS);

    }
}



void main_initialise()
{
    // piloteDetectionPiece_initialise();
    // piloteElectroaimant_initialise();
    // piloteLimitSwitchX_initialise();
    // piloteLimitSwitchY_initialise();
    // piloteMoteurGauche_initialise();
    // piloteMoteurDroit_initialise();
    piloteUart2_initialise();    
    // detectionPiece_initialise();
    taskTxUart_initialise();
    taskRxUart_initialise();
}



