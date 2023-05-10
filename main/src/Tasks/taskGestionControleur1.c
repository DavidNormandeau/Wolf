//taskGestionControleur1:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "taskDeplacementPiece.h"
#include "taskCalibration.h"
#include "taskGestionControleur1.h"

//Definitions privees
static const char* TAG = "TASK GESTION CONTROLEUR1";

//Declarations de fonctions privees:
void taskGestionControleur1_attendFinCalibration();
void taskGestionControleur1_attendCommande();
void taskGestionControleur1_attendFinDeplacementPiece();
void taskGestionControleur1_attendCommandeTestPosition();
void taskGestionControleur1_attendCommandeTestPositionNouvellePartie();
void taskGestionControleur1_etatEnErreur();

//Definitions de variables privees:
void (*taskGestionControleur1_execute)(void);


//Definitions de fonctions privees:
// void taskGestionControleur1_attendFinCalibration()
// {
//     xSemaphoreGive(semaphoreDebutCalibration);
//     ESP_LOGI(TAG, "Calibration en cours...");
//     if(calibration.requete == REQUETE_ACTIVE)
//     {
//         return;
//     }
//     if(calibration.statut == TASKCALIBRATION_ERREUR)
//     {
//         taskGestionControleur1_execute = taskGestionControleur1_etatEnErreur;
//     }

//     taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
// }

void taskGestionControleur1_attendCommande()
{
    
}

void taskGestionControleur1_attendFinDeplacementPiece()
{
    if(deplacementPiece.requete == REQUETE_ACTIVE)
    {
        return;
    }

    
    if(deplacementPiece.statut == DEPLACEMENTPIECE_ERREUR)
    {
       taskGestionControleur1_execute = taskGestionControleur1_attendCommandeTestPosition;
       return; 
    }

    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
}

void taskGestionControleur1_attendCommandeTestPosition()
{

}

void taskGestionControleur1_attendCommandeTestPositionNouvellePartie()
{

}

void taskGestionControleur1_etatEnErreur()
{

}










//Definitions de variables publiques:
QueueHandle_t queueGestionControleur1;
TaskHandle_t xHandleTaskGestionControleur1;
 

//Definitions de fonctions publiques:
void taskGestionControleur1(void *pvParameters)
{
    info_deplacement_t deplacementAFaire;
    unsigned char message[5] = {0};
    TickType_t lastWakeTime;
   
    

    
    if(queueDeplacementPiece == 0)
    {
        ESP_LOGE(TAG, "queueDeplacementPiece n'a pas été créé!");
    }

    if(semaphoreDebutCalibration == NULL)
    {
        ESP_LOGE(TAG, "semaphoreCalibration n'a pas été créé!");
    }

    taskGestionControleur1_execute = taskGestionControleur1_attendFinCalibration;

    lastWakeTime = xTaskGetTickCount();
    
    while(1)
    {
        
        
        switch(message[0])
        {
            // case 'M':
            //     break;

            case 'C':
                xSemaphoreGive(semaphoreDebutCalibration);
                ESP_LOGI(TAG, "Calibration en cours...");
                //envoyer que calibration termininée
                break;

            // case 'B':
            //     break;
            
            case 'c':
                break;

        }

        xTaskDelayUntil(&lastWakeTime, 50/portTICK_PERIOD_MS);
      
    }

    vTaskDelete(xHandleTaskGestionControleur1);
}





void taskGestionControleur1_initialise(void)
{
    queueGestionControleur1 = xQueueCreate(5, sizeof(unsigned char));                             //à déterminer
    xTaskCreatePinnedToCore(taskGestionControleur1, 
                            "Task Gestion Controleur 1", 
                            TASKGESTIONCONTROLEUR1_STACK_SIZE, 
                            NULL, 
                            TASKGESTIONCONTROLEUR1_PRIORITY, 
                            &xHandleTaskGestionControleur1, 
                            TASKGESTIONCONTROLEUR1_CORE
    );
}