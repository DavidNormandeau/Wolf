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
static const char* TAG = "MAIN";

//Declarations de fonctions privees:
void main_initialise();

//Definitions de variables publiques:
unsigned char tabPieceDetecteeSurEchiquier[64];


//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void app_main(void)
{
    main_initialise();    

    while(1)
    {
        //Test coreXY
        // ESP_LOGI(TAG, "H1 to A8");
        // coreXY_deplaceEnNombreDeSteps(500, H1_TO_A8, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "8 to 1");
        // coreXY_deplaceEnNombreDeSteps(500, _8_TO_1, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "A1 to H8");
        // coreXY_deplaceEnNombreDeSteps(500, A1_TO_H8, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "H to A");
        // coreXY_deplaceEnNombreDeSteps(500, H_TO_A, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "A8 to H1");
        // coreXY_deplaceEnNombreDeSteps(500, A8_TO_H1, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "1 to 8");
        // coreXY_deplaceEnNombreDeSteps(500, _1_TO_8, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "H8 to A1");
        // coreXY_deplaceEnNombreDeSteps(500, H8_TO_A1, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "A to H");        
        // coreXY_deplaceEnNombreDeSteps(500, A_TO_H, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);

        //TEST detection
        int i;
        detectionPiece_litLEchiquier(tabPieceDetecteeSurEchiquier);
        printf("---------------------------------------\r\n");
        for(i = 0; i< 64; i++)
        {
            printf("| %d ", tabPieceDetecteeSurEchiquier[i]);
            if(i % 8 == 0)
            {
              printf("|\r\n----------------------------------\r\n");  
            }
            
        }
        printf("\r\n\r\n\r\n");

        vTaskDelay(1000/portTICK_PERIOD_MS);
        
        
        
    }
}



void main_initialise()
{
    piloteDetectionPiece_initialise();
    // piloteElectroaimant_initialise();
    // piloteLimitSwitchX_initialise();
    // piloteLimitSwitchY_initialise();
    // piloteMoteurGauche_initialise();
    // piloteMoteurDroit_initialise();
    // piloteUart2_initialise();    
    detectionPiece_initialise();
    //electroaimant_initialise();
    // coreXY_initialise();
    // taskTxUart_initialise();
    // taskRxUart_initialise();
}



