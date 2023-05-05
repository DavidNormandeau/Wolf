//taskGestionControleur1:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "taskDeplacementPiece.h"
#include "taskGestionControleur1.h"

//Definitions privees
static const char* TAG = "TASK GESTION CONTROLEUR1";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
TaskHandle_t xHandleTaskGestionControleur1;


//Definitions de fonctions publiques:
void taskGestionControleur1(void *pvParameters)
{
    info_deplacement_t deplacementAFaire;
    unsigned char message[5] = {0};

    queueDeplacementPiece = xQueueCreate(5, sizeof(deplacementAFaire));
    semaphoreCalibration = xSemaphoreCreateBinary();
    

    
    if(queueDeplacementPiece == 0)
    {
        ESP_LOGE(TAG, "queueDeplacementPiece n'a pas été créé!");
    }

    if(semaphoreCalibration == NULL)
    {
        ESP_LOGE(TAG, "semaphoreCalibration n'a pas été créé!");
    }
    
    while(1)
    {
        switch(message[0])
        {
            // case 'M':
            //     break;

            case 'C':
                xSemaphoreGive(semaphoreCalibration);
                ESP_LOGI(TAG, "Calibration en cours...");
                //envoyer que calibration termininée
                break;

            // case 'B':
            //     break;
            
            case 'c':
                break;

        }
      
    }

    vTaskDelete(xHandleTaskGestionControleur1);
}





void taskGestionControleur1_initialise(void)
{
    xTaskCreatePinnedToCore(taskGestionControleur1, 
                            "Task Gestion Controleur 1", 
                            TASKGESTIONCONTROLEUR1_STACK_SIZE, 
                            NULL, 
                            TASKGESTIONCONTROLEUR1_PRIORITY, 
                            &xHandleTaskGestionControleur1, 
                            TASKGESTIONCONTROLEUR1_CORE
    );
}