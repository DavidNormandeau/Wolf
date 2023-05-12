//taskGestionControleur1:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "taskDeplacementPiece.h"
#include "taskCalibration.h"
#include "taskRxUart.h"
#include "taskTxUart.h"
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
void taskGestionControleur1_prepareMessageATransmettre(char* message, unsigned char longeur);

//Definitions de variables privees:
void (*taskGestionControleur1_execute)(void);
TASKRXUART taskGestionControleur1_messageRecu;
TASKTXUART taskGestionControleur1_messageATransmettre;



//Definitions de fonctions privees:
void taskGestionControleur1_attendFinCalibration()
{
    ESP_LOGI(TAG, "Calibration en cours...");
    xSemaphoreTake(semaphoreFinCalibration, portMAX_DELAY);  //delay à déterminer par le temps, envoyer une erreur si prend trop de temps
    {
        ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendFinCalibration - Reception queueGestionControleur failed");
    }

    // if(calibration.statut == TASKCALIBRATION_ERREUR)
    // {
    //     taskGestionControleur1_execute = taskGestionControleur1_etatEnErreur;
    // }

    
    //envoyer que calibration termininée
    taskGestionControleur1_prepareMessageATransmettre("C1", 2);
    xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);

    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
}

void taskGestionControleur1_attendCommande()
{
    if(xQueueReceive(queueRxUart, &taskGestionControleur1_messageRecu, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGE(TAG, "Erreur: Reception QueueRxUart failed");
    }

    switch(taskGestionControleur1_messageRecu.octetsRecus[0])
    {
        //Suspendre des tasks lorsqu'en mode HvsH
        // case 'M':
        //     break;

        case 'C':
            xSemaphoreGive(semaphoreDebutCalibration);
            ESP_LOGI(TAG, "Calibration en cours...");
            taskGestionControleur1_execute = taskGestionControleur1_attendFinCalibration;
            break;

        case 'N':
            taskGestionControleur1_execute = taskGestionControleur1_attendCommandeTestPositionNouvellePartie;
            break;
        
        case 'c':
            taskGestionControleur1_execute = taskGestionControleur1_attendFinDeplacementPiece;
            break;

    }
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
    
    
    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
}

void taskGestionControleur1_attendCommandeTestPositionNouvellePartie()
{


    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
}

void taskGestionControleur1_etatEnErreur()
{
    ESP_LOGE(TAG, "ETAT EN ERREUR");

    //Pour l'instant bloc à l'infini
}

void taskGestionControleur1_prepareMessageATransmettre(char* message, unsigned char longueur)
{
    unsigned char i;

    taskGestionControleur1_messageATransmettre.nombreOctetsATransmettre = longueur;
    for(i = 0; i < longueur; i++)
    {
        taskGestionControleur1_messageATransmettre.octetsATransmettre[i] = message[i];
    }
}










//Definitions de variables publiques:
QueueHandle_t queueGestionControleur1;
TaskHandle_t xHandleTaskGestionControleur1;
 

//Definitions de fonctions publiques:
void taskGestionControleur1(void *pvParameters)
{
    // info_deplacement_t deplacementAFaire;
    // unsigned char message[5] = {0};
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
    
    //Fait une calibration dès la mise en marche 
    xSemaphoreGive(semaphoreDebutCalibration);
    lastWakeTime = xTaskGetTickCount();    
    while(1)
    {
        
        taskGestionControleur1_execute();


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