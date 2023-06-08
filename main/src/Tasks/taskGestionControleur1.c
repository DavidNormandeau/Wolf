//taskGestionControleur1:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "detectionPiece.h"
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
void taskGestionControleur1_etatEnErreur();
void taskGestionControleur1_prepareMessageATransmettre(char* message, unsigned char longeur);
void taskGestionControleur1_prepareLaTransmissionDeLaPositionDesPieces();
void taskGestionControleur1_prepareDeplacementAFaire();
unsigned char taskGestionControleur1_testBonDeplacementDeLaPiece();

//Fonction pour TEST
void test_affichePositionPieceSurMonitor();

//Definitions de variables privees:
void (*taskGestionControleur1_execute)(void);
TASKRXUART taskGestionControleur1_messageRecu;
TASKTXUART taskGestionControleur1_messageATransmettre;
info_deplacement_t taskGestionControleur1_deplacementRecu;
position_piece_t positionEchiquierPourTransmission;



//Definitions de fonctions privees:
void taskGestionControleur1_attendFinCalibration()
{
    ESP_LOGI(TAG, "Calibration en cours...");
    if(xSemaphoreTake(semaphoreFinCalibration, (30000/portTICK_PERIOD_MS)) != pdTRUE)                            //delay à déterminer par le temps, envoyer une erreur si prend trop de temps??????
    {
        ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendFinCalibration - Timeout Calibration");
        taskGestionControleur1_prepareMessageATransmettre("C0", 2);
        taskGestionControleur1_execute = taskGestionControleur1_etatEnErreur;
        return;
    }

    ESP_LOGI(TAG, "Calibration Termininée");    
    //envoyer que calibration termininée
    taskGestionControleur1_prepareMessageATransmettre("C1", 2);
    xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);

    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
}

void taskGestionControleur1_attendCommande()
{
    ESP_LOGI(TAG, "taskGestionControleur1_attendCommande");
    if(xQueueReceive(queueRxUart, &taskGestionControleur1_messageRecu, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendCommande - Reception QueueRxUart failed");
        return;
    }

    switch(taskGestionControleur1_messageRecu.octetsRecus[0])
    {
        case 'C':
            xSemaphoreGive(semaphoreDebutCalibration);
            ESP_LOGI(TAG, "Calibration en cours...");
            taskGestionControleur1_execute = taskGestionControleur1_attendFinCalibration;
            break;
        
        case 'c':
            taskGestionControleur1_prepareDeplacementAFaire();
            if(xQueueSend(queueDeplacementPiece, &taskGestionControleur1_deplacementRecu, 50 / portTICK_PERIOD_MS) != pdTRUE)
            {
                ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendCommande - queueDeplacementPiece est plein.");
            }
            taskGestionControleur1_execute = taskGestionControleur1_attendFinDeplacementPiece;
            break;
        
        case 'P':              
            detectionPiece_litLEchiquier8x8(tabPieceDetecteeSurEchiquier);
            taskGestionControleur1_prepareLaTransmissionDeLaPositionDesPieces();                                              
            xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
            break;


    }
    return;
}

void taskGestionControleur1_attendFinDeplacementPiece()
{
    ESP_LOGI(TAG, "taskGestionControleur1_attendFinDeplacementPiece");
    if(xSemaphoreTake(semaphoreFinDeplacementPiece, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendFinDeplacementPiece - Timeout xSemaphoreTake");
        taskGestionControleur1_execute = taskGestionControleur1_etatEnErreur;
        return;
    }

    //DÉPLACEMENT RÉUSSI
    ESP_LOGI(TAG, "Déplacement fini");
    taskGestionControleur1_prepareMessageATransmettre("c1", 2);
    xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);

    detectionPiece_litLEchiquier8x8(tabPieceDetecteeSurEchiquier);
    taskGestionControleur1_prepareLaTransmissionDeLaPositionDesPieces();                                              
    xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);

    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
}


void taskGestionControleur1_etatEnErreur()
{
    ESP_LOGE(TAG, "taskGestionControleur1_etatEnErreur");
    vTaskDelay(1000/portTICK_PERIOD_MS);

    //Pour l'instant, bloque à l'infini
}

//------------------------------------------------------------------------------


void taskGestionControleur1_prepareMessageATransmettre(char* message, unsigned char longueur)
{
    unsigned char i;

    taskGestionControleur1_messageATransmettre.nombreOctetsATransmettre = longueur;
    for(i = 0; i < longueur; i++)
    {
        taskGestionControleur1_messageATransmettre.octetsATransmettre[i] = message[i];
    }
}

void taskGestionControleur1_prepareLaTransmissionDeLaPositionDesPieces()
{
    unsigned char file, rank, i;

    positionEchiquierPourTransmission.entier64 = 0;
    for(rank = RANK_1; rank <= RANK_8; rank++)
    {
        for(file = FILE_A; file <= FILE_H; file++)
        {
            positionEchiquierPourTransmission.entier64 = positionEchiquierPourTransmission.entier64 << 1;
            positionEchiquierPourTransmission.entier64 = positionEchiquierPourTransmission.entier64 | tabPieceDetecteeSurEchiquier[file][rank]; 
        }
    }

    taskGestionControleur1_messageATransmettre.nombreOctetsATransmettre = 9;
    taskGestionControleur1_messageATransmettre.octetsATransmettre[0] = 'P';
    for(i = 1; i < 9; i++)
    {
        taskGestionControleur1_messageATransmettre.octetsATransmettre[i] = positionEchiquierPourTransmission.cTab[i-1];
        ESP_LOGW(TAG, "%d: 0x%02X", i, taskGestionControleur1_messageATransmettre.octetsATransmettre[i]);
    }
}

void taskGestionControleur1_prepareDeplacementAFaire()
{    
    taskGestionControleur1_deplacementRecu.type                  = taskGestionControleur1_messageRecu.octetsRecus[1];
    taskGestionControleur1_deplacementRecu.positionDepart.file   = taskGestionControleur1_messageRecu.octetsRecus[2];
    taskGestionControleur1_deplacementRecu.positionDepart.rank   = taskGestionControleur1_messageRecu.octetsRecus[3];
    taskGestionControleur1_deplacementRecu.positionArrivee.file  = taskGestionControleur1_messageRecu.octetsRecus[4];
    taskGestionControleur1_deplacementRecu.positionArrivee.rank  = taskGestionControleur1_messageRecu.octetsRecus[5];

    ESP_LOGI(TAG, "DeplacementAFaire: type: %d, depart.file: %d depart.rank: %d, arrivee.file: %d, arrivee.rank: %d", 
        taskGestionControleur1_deplacementRecu.type,
        taskGestionControleur1_deplacementRecu.positionDepart.file,
        taskGestionControleur1_deplacementRecu.positionDepart.rank,
        taskGestionControleur1_deplacementRecu.positionArrivee.file,
        taskGestionControleur1_deplacementRecu.positionArrivee.rank );
}


void test_affichePositionPieceSurMonitor()
{
        //TEST detection 8x8
        int rank, file;
        detectionPiece_litLEchiquier8x8(tabPieceDetecteeSurEchiquier);

        printf("---------------------------------\r\n");
        for(rank = RANK_1; rank <= RANK_8; rank++)
        {
            for(file = FILE_A; file <= FILE_H; file++)
            {
                printf("| %d ", tabPieceDetecteeSurEchiquier[file][rank]); 
            }
            printf("|\r\n---------------------------------\r\n");  
           
        }
        printf("\r\n\r\n\r\n");
}







//Definitions de variables publiques:
QueueHandle_t queueGestionControleur1;
TaskHandle_t xHandleTaskGestionControleur1;
 

//Definitions de fonctions publiques:
void taskGestionControleur1(void *pvParameters)
{
    TickType_t lastWakeTime;    

    
    if(queueDeplacementPiece == 0)
    {
        ESP_LOGE(TAG, "queueDeplacementPiece n'a pas été créé!");
    }

    if(semaphoreDebutCalibration == NULL)
    {
        ESP_LOGE(TAG, "semaphoreCalibration n'a pas été créé!");
    }

    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;    


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
    queueGestionControleur1 = xQueueCreate(5, sizeof(unsigned char));                             
    xTaskCreatePinnedToCore(taskGestionControleur1, 
                            "Task Gestion Controleur 1", 
                            TASKGESTIONCONTROLEUR1_STACK_SIZE, 
                            NULL, 
                            TASKGESTIONCONTROLEUR1_PRIORITY, 
                            &xHandleTaskGestionControleur1, 
                            TASKGESTIONCONTROLEUR1_CORE
    );
}