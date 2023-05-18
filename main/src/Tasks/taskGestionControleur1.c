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
#define POSITION_DE_DEPART_INT64 0xFF0000FF
#define POSITION_DES_PIECES_EST_EN_ERREUR   0
#define POSITION_DES_PIECES_EST_BONNE       1

//Declarations de fonctions privees:
void taskGestionControleur1_attendFinCalibration();
void taskGestionControleur1_attendCommande();
void taskGestionControleur1_attendFinDeplacementPiece();
void taskGestionControleur1_attendCommandeTestPosition();
void taskGestionControleur1_attendCommandeTestPositionNouvellePartie();
void taskGestionControleur1_etatEnErreur();
void taskGestionControleur1_prepareMessageATransmettre(char* message, unsigned char longeur);
unsigned char taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquier();
void taskGestionControleur1_prepareDeplacementAFaire();
unsigned char taskGestionControleur1_testBonDeplacementDeLaPiece();

//Definitions de variables privees:
void (*taskGestionControleur1_execute)(void);
TASKRXUART taskGestionControleur1_messageRecu;
TASKTXUART taskGestionControleur1_messageATransmettre;
info_deplacement_t taskGestionControleur1_deplacementAFaire;



//Definitions de fonctions privees:
void taskGestionControleur1_attendFinCalibration()
{
    ESP_LOGI(TAG, "Calibration en cours...");
    xSemaphoreTake(semaphoreFinCalibration, portMAX_DELAY);  //delay à déterminer par le temps, envoyer une erreur si prend trop de temps
    {
        ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendFinCalibration - Timeout Calibration");
        taskGestionControleur1_prepareMessageATransmettre("C0", 2);
        taskGestionControleur1_execute = taskGestionControleur1_etatEnErreur;
        return;
    }

    ESP_LOGI(TAG, "Calibration Termininée");

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
    ESP_LOGI(TAG, "taskGestionControleur1_attendCommande");
    if(xQueueReceive(queueRxUart, &taskGestionControleur1_messageRecu, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendCommande - Reception QueueRxUart failed");
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
            taskGestionControleur1_prepareDeplacementAFaire();
            if(xQueueSend(queueDeplacementPiece, &taskGestionControleur1_deplacementAFaire, 50 / portTICK_PERIOD_MS) != pdTRUE)
            {
                ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendCommande - queueDeplacementPiece est plein.");
            }
            taskGestionControleur1_execute = taskGestionControleur1_attendFinDeplacementPiece;
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

    // pieceDetecteeSurEchiquierPrecedent.entier64 = pieceDetecteeSurEchiquier.entier64;
    // detectionPiece_litLEchiquierInt64(&pieceDetecteeSurEchiquier.entier64); 
    // if(taskGestionControleur1_testBonDeplacementDeLaPiece() == POSITION_DES_PIECES_EST_EN_ERREUR)
    // {
    //     //DÉPLACEMENT EN ÉCHEC
    //     ESP_LOGI(TAG, "Déplacement échec");
    //     taskGestionControleur1_prepareMessageATransmettre("E1", 2);
    //     xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
    //     //taskGestionControleur1_prepareMessageATransmettre("P", 8);                                                 //à compléter
    //     //xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
 
    //    taskGestionControleur1_execute = taskGestionControleur1_attendCommandeTestPosition;
    //    return; 
    // }

    //DÉPLACEMENT RÉUSSI
    ESP_LOGI(TAG, "Déplacement Réussi");
    taskGestionControleur1_prepareMessageATransmettre("C1", 2);
    xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
}

void taskGestionControleur1_attendCommandeTestPosition()
{
    ESP_LOGI(TAG, "taskGestionControleur1_attendCommandeTestPosition");
    if(xQueueReceive(queueRxUart, &taskGestionControleur1_messageRecu, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendCommandeTestPosition - Reception QueueRxUart failed");
        //Allez en etatErreur?????
        return;
    }

    if(taskGestionControleur1_messageRecu.octetsRecus[0] != 'B')
    {
        return;           
    }
    
    if(taskGestionControleur1_messageRecu.octetsRecus[1] == BOUTON_A_ETE_APPUYE || taskGestionControleur1_messageRecu.octetsRecus[2] == BOUTON_A_ETE_APPUYE)
    {
        pieceDetecteeSurEchiquierPrecedent.entier64 = pieceDetecteeSurEchiquier.entier64;
        detectionPiece_litLEchiquierInt64(&pieceDetecteeSurEchiquier.entier64);
        //à vérifier
        if(taskGestionControleur1_testBonDeplacementDeLaPiece())
        {
           
           taskGestionControleur1_prepareMessageATransmettre("E1", 2);
           xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
           //taskGestionControleur1_prepareMessageATransmettre("P", 8);                                                 //à compléter
           //xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);

           return; 
        }
        

    }
    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
    
    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;
}

void taskGestionControleur1_attendCommandeTestPositionNouvellePartie()
{
    ESP_LOGI(TAG, "taskGestionControleur1_attendCommandeTestPositionNouvellePartie");
    if(xQueueReceive(queueRxUart, &taskGestionControleur1_messageRecu, portMAX_DELAY) != pdTRUE)
    {
        ESP_LOGE(TAG, "Erreur: taskGestionControleur1_attendCommandeTestPositionNouvellePartie - Reception QueueRxUart failed");
        //Allez en etatErreur?????
        return;
    }

    if(taskGestionControleur1_messageRecu.octetsRecus[0] != 'B')
    {
        return;           
    }

    if( taskGestionControleur1_messageRecu.octetsRecus[1] == BOUTON_PAS_ETE_APPUYE && 
        taskGestionControleur1_messageRecu.octetsRecus[2] == BOUTON_PAS_ETE_APPUYE)
    {
        return;   
    }
    
    // detectionPiece_litLEchiquier(tabPieceDetecteeSurEchiquier);
    detectionPiece_litLEchiquierInt64(&pieceDetecteeSurEchiquier.entier64);
    if(taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquier() == POSITION_DES_PIECES_EST_EN_ERREUR)
    {
        taskGestionControleur1_prepareMessageATransmettre("E1", 2);
        xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
        //taskGestionControleur1_prepareMessageATransmettre("P", 8);                                                 //à compléter
        //xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);

        return; 
    }

    //peut-etre message pour dire que la position est bonne??????????
    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;    
}

void taskGestionControleur1_etatEnErreur()
{
    ESP_LOGE(TAG, "taskGestionControleur1_etatEnErreur");

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

// unsigned char taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquier()
// {
//     unsigned char i;
//     unsigned char statut = 0;

//     for(i = 0; i < 64; i++)
//     {
//         if(i < 16 || i > 47)    //Rank 1, 2, 7, 8
//         {
//             if(detectionPiece_litLaCase(i) == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
//             {
//                 statut++;
//             }
//         }
//         else
//         {
//             if(detectionPiece_litLaCase(i) == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
//             {
//                 statut++;
//             }
//         }

//     }
//     return statut;
// }

unsigned char taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquier()
{
    unsigned char statut = POSITION_DES_PIECES_EST_EN_ERREUR;

    if(pieceDetecteeSurEchiquier.entier64 == POSITION_DE_DEPART_INT64)
    {
        statut = POSITION_DES_PIECES_EST_BONNE;
    }

    return statut;
}

void taskGestionControleur1_prepareLaPositionDesPiecesPourLaTransmission()
{

}

void taskGestionControleur1_prepareDeplacementAFaire()
{
    taskGestionControleur1_deplacementAFaire.type                  = taskGestionControleur1_messageRecu.octetsRecus[1];
    taskGestionControleur1_deplacementAFaire.positionDepart.file   = 2 * taskGestionControleur1_messageRecu.octetsRecus[2] + 1;
    taskGestionControleur1_deplacementAFaire.positionDepart.rank   = 2 * taskGestionControleur1_messageRecu.octetsRecus[3] + 1;
    taskGestionControleur1_deplacementAFaire.positionArrivee.file  = 2 * taskGestionControleur1_messageRecu.octetsRecus[4] + 1;
    taskGestionControleur1_deplacementAFaire.positionArrivee.rank  = 2 * taskGestionControleur1_messageRecu.octetsRecus[5] + 1;
    ESP_LOGI(TAG, "DeplacementAFaire: type: %d, depart.file: %d depart.rank: %d, arrivee.file: %d, arrivee.rank: %d", 
        taskGestionControleur1_deplacementAFaire.type,
        taskGestionControleur1_deplacementAFaire.positionDepart.file,
        taskGestionControleur1_deplacementAFaire.positionDepart.rank,
        taskGestionControleur1_deplacementAFaire.positionArrivee.file,
        taskGestionControleur1_deplacementAFaire.positionArrivee.rank );
}

unsigned char taskGestionControleur1_testBonDeplacementDeLaPiece()
{
    unsigned char positionValide = POSITION_DES_PIECES_EST_BONNE;

    //CAPTURE OU NORMAL
    if(taskGestionControleur1_deplacementAFaire.type == CAPTURE_A_FAIRE || taskGestionControleur1_deplacementAFaire.type == NORMAL)
    {
        if(tabPieceDetecteeSurEchiquier[taskGestionControleur1_deplacementAFaire.positionDepart.file][taskGestionControleur1_deplacementAFaire.positionDepart.rank] 
            == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }

        if(tabPieceDetecteeSurEchiquier[taskGestionControleur1_deplacementAFaire.positionArrivee.file][taskGestionControleur1_deplacementAFaire.positionArrivee.rank] 
            == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;    
        }
    }
    //EN PASSANT
    else if(taskGestionControleur1_deplacementAFaire.type == EN_PASSANT)
    {
        if(tabPieceDetecteeSurEchiquier[taskGestionControleur1_deplacementAFaire.positionDepart.file][taskGestionControleur1_deplacementAFaire.positionDepart.rank]  //Pour noir seulement 
            == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }

        if(tabPieceDetecteeSurEchiquier[taskGestionControleur1_deplacementAFaire.positionArrivee.file][taskGestionControleur1_deplacementAFaire.positionArrivee.rank] 
            == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;    
        }

        if(tabPieceDetecteeSurEchiquier[taskGestionControleur1_deplacementAFaire.positionArrivee.file][taskGestionControleur1_deplacementAFaire.positionArrivee.rank - 1] 
            == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;    
        }
    }
    else if(taskGestionControleur1_deplacementAFaire.type == ROQUE_COURT_BLANC)
    {
        //à compléter
    }
    else if(taskGestionControleur1_deplacementAFaire.type == ROQUE_COURT_NOIR)
    {
        //à compléter
    }
    else if(taskGestionControleur1_deplacementAFaire.type == ROQUE_LONG_BLANC)
    {
        //à compléter
    }
    else if(taskGestionControleur1_deplacementAFaire.type == ROQUE_LONG_NOIR)
    {
        //à compléter
    }

    return positionValide;
}










//Definitions de variables publiques:
QueueHandle_t queueGestionControleur1;
TaskHandle_t xHandleTaskGestionControleur1;
 

//Definitions de fonctions publiques:
void taskGestionControleur1(void *pvParameters)
{
    // info_deplacement_t taskGestionControleur1_deplacementAFaire;
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

    // pieceDetecteeSurEchiquier.entier64 = 0xFFFFFFFF;
    // pieceDetecteeSurEchiquierPrecedent.entier64 = 0xFFFFFFFF;
    
    taskGestionControleur1_execute = taskGestionControleur1_attendCommande;//taskGestionControleur1_attendFinCalibration;
    
    //Fait une calibration dès la mise en marche 
    //xSemaphoreGive(semaphoreDebutCalibration);        //à remettre apres test
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