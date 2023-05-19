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
void taskGestionControleur1_prepareLaTransmissionDeLaPositionDesPieces();
unsigned char taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquier();
unsigned char taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquierInt64();
void taskGestionControleur1_prepareDeplacementAFaire();
unsigned char taskGestionControleur1_testBonDeplacementDeLaPiece();
void taskGestionControleur1_enregistreLaPositionDeLEchiquier();

//Definitions de variables privees:
void (*taskGestionControleur1_execute)(void);
TASKRXUART taskGestionControleur1_messageRecu;
TASKTXUART taskGestionControleur1_messageATransmettre;
info_deplacement_t taskGestionControleur1_deplacementAFaire;
position_piece_t positionEchiquierPourTransmission;



//Definitions de fonctions privees:
void taskGestionControleur1_attendFinCalibration()
{
    ESP_LOGI(TAG, "Calibration en cours...");
    if(xSemaphoreTake(semaphoreFinCalibration, portMAX_DELAY) != pdTRUE)  //delay à déterminer par le temps, envoyer une erreur si prend trop de temps
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
    //*************EN REMETTRE LORSQUE JAI MET AIMANT**********************************
    
    // taskGestionControleur1_enregistreLaPositionDeLEchiquier();       
    // detectionPiece_litLEchiquier8x8(tabPieceDetecteeSurEchiquier); 
    // if(taskGestionControleur1_testBonDeplacementDeLaPiece() == POSITION_DES_PIECES_EST_EN_ERREUR)
    // {
    //     //DÉPLACEMENT EN ÉCHEC
    //     ESP_LOGI(TAG, "Déplacement échec");
    //     taskGestionControleur1_prepareMessageATransmettre("E1", 2);
    //     xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
    //     taskGestionControleur1_prepareLaTransmissionDeLaPositionDesPieces();
    //     xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
 
    //    taskGestionControleur1_execute = taskGestionControleur1_attendCommandeTestPosition;
    //    return; 
    // }

    //DÉPLACEMENT RÉUSSI
    ESP_LOGI(TAG, "Déplacement Réussi");
    taskGestionControleur1_prepareMessageATransmettre("c1", 2);
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
        taskGestionControleur1_enregistreLaPositionDeLEchiquier();       
        detectionPiece_litLEchiquier8x8(tabPieceDetecteeSurEchiquier); 
        //à vérifier
        if(taskGestionControleur1_testBonDeplacementDeLaPiece() == POSITION_DES_PIECES_EST_EN_ERREUR)
        {
           
           taskGestionControleur1_prepareMessageATransmettre("E1", 2);
           xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
           taskGestionControleur1_prepareLaTransmissionDeLaPositionDesPieces();                                              
           xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);

           return; 
        }
    }
    //peut-être dire que la position est bonne???????????????????
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
    
    taskGestionControleur1_enregistreLaPositionDeLEchiquier();       
    detectionPiece_litLEchiquier8x8(tabPieceDetecteeSurEchiquier); 
    if(taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquier() == POSITION_DES_PIECES_EST_EN_ERREUR)
    {
        taskGestionControleur1_prepareMessageATransmettre("E1", 2);
        xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);
        taskGestionControleur1_prepareLaTransmissionDeLaPositionDesPieces();                                                 
        xQueueSend(queueTxUart, &taskGestionControleur1_messageATransmettre, 50/portTICK_PERIOD_MS);

        return; 
    }

    //peut-etre message pour dire que la position est bonne??????????
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

unsigned char taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquier()
{
    unsigned char file, rank;

    for(rank = 0; rank < 8; rank++)
    {
        for(file = 0; file < 8; file++)
        {
            if(rank == 0 || rank == 1 || rank == 6 || rank == 7)
            {
                if(tabPieceDetecteeSurEchiquier[file][rank] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
                {
                    return POSITION_DES_PIECES_EST_EN_ERREUR;
                }
            }

            if(rank >= 2 && rank <= 5)
            {
                if(tabPieceDetecteeSurEchiquier[file][rank] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
                {
                    return POSITION_DES_PIECES_EST_EN_ERREUR;
                }
            }
        }
    }

    return POSITION_DES_PIECES_EST_BONNE;
}

unsigned char taskGestionControleur1_verifieLaPositionDeDepartDeLEchiquierInt64()
{
    if(pieceDetecteeSurEchiquier.entier64 == POSITION_DE_DEPART_INT64)
    {
        return POSITION_DES_PIECES_EST_BONNE;
    }

    return POSITION_DES_PIECES_EST_EN_ERREUR;
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
    }
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
        if(tabPieceDetecteeSurEchiquier[FILE_F][RANK_1] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_G][RANK_1] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_E][RANK_1] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_H][RANK_1] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }

        //return POSITION_DES_PIECES_EST_BONNE;
    }
    else if(taskGestionControleur1_deplacementAFaire.type == ROQUE_COURT_NOIR)
    {
        if(tabPieceDetecteeSurEchiquier[FILE_F][RANK_8] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_G][RANK_8] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_E][RANK_8] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_H][RANK_8] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        
        //return POSITION_DES_PIECES_EST_BONNE;        
    }
    else if(taskGestionControleur1_deplacementAFaire.type == ROQUE_LONG_BLANC)
    {
        if(tabPieceDetecteeSurEchiquier[FILE_C][RANK_1] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_D][RANK_1] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_E][RANK_1] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_A][RANK_1] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        
        //return POSITION_DES_PIECES_EST_BONNE;        
    }
    else if(taskGestionControleur1_deplacementAFaire.type == ROQUE_LONG_NOIR)
    {
        if(tabPieceDetecteeSurEchiquier[FILE_C][RANK_8] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_D][RANK_8] == DETECTIONPIECE_VALEUR_SI_CASE_VIDE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_E][RANK_8] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        if(tabPieceDetecteeSurEchiquier[FILE_A][RANK_8] == DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE)
        {
            return POSITION_DES_PIECES_EST_EN_ERREUR;
        }
        
        //return POSITION_DES_PIECES_EST_BONNE;
    }

    return POSITION_DES_PIECES_EST_BONNE;
}

void taskGestionControleur1_enregistreLaPositionDeLEchiquier()
{
    unsigned char rank, file;

    for(rank = RANK_1; rank <= RANK_8; rank++)
    {
        for(file = FILE_A; file <= FILE_H; file++)
        {
            tabPieceDetecteeSurEchiquierPrecedent[file][rank] = tabPieceDetecteeSurEchiquier[file][rank];
        }
    }
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

    // pieceDetecteeSurEchiquier.entier64 = 0xFFFFFFFF;
    // pieceDetecteeSurEchiquierPrecedent.entier64 = 0xFFFFFFFF;
    
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