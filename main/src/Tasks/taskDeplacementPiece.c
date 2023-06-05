//taskDeplacementPiece:
//Historique: 
// 2023-05-02, David Normandeau, creation

//INCLUSIONS
#include <stdlib.h>
#include "define.h"
#include "electroaimant.h"
#include "coreXY.h"
#include "taskDeplacementPiece.h"

//Definitions privees
static const char* TAG = "TASK DEPLACEMENT PIECE";
#define VITESSE_LENTE           3   //en ms
#define VITESSE_RAPIDE          1   //en ms
#define ELECTROAIMANT_ETEINT    0
#define ELECTROAIMANT_ACTIF     1

//Declarations de fonctions privees:
void deplaceALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale, unsigned char vitesse, unsigned char aimante);
void deplaceEnDiagonalALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale, unsigned char vitesse, unsigned char aimante);
void deplaceCavalierALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale);
void deplaceRoqueCourtBlanc();
void deplaceRoqueLongBlanc();
void deplaceRoqueCourtNoir();
void deplaceRoqueLongNoir();
void taskDeplacementPiece_prepareDeplacementAFaire();

//Definitions de variables privees:
info_deplacement_t taskDeplacementPiece_deplacementAFaire;

//Definitions de fonctions privees:
void deplaceALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale, unsigned char vitesse, unsigned char aimante)
{
    unsigned int deplacementXenSteps, deplacementYenSteps;

    if(aimante == ELECTROAIMANT_ACTIF)
    {
        electroaimant_active();
    }


    deplacementXenSteps = abs((int)((positionFinale.file - positionInitiale.file) * NBRE_DE_STEP_DANS_UNE_DEMI_CASE));
    deplacementYenSteps = abs((int)((positionFinale.rank - positionInitiale.rank) * NBRE_DE_STEP_DANS_UNE_DEMI_CASE));
    
    ESP_LOGI(TAG, "deplacementXenSteps: %d, deplacementYenSteps: %d", deplacementXenSteps, deplacementYenSteps);

    if(positionFinale.file > positionInitiale.file)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, A_TO_H, vitesse);
    }
    else if(positionFinale.file < positionInitiale.file)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, H_TO_A, vitesse);
    }

    if(positionFinale.rank > positionInitiale.rank)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _1_TO_8, VITESSE_RAPIDE);
    }
    else if(positionFinale.rank < positionInitiale.rank)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _8_TO_1, VITESSE_RAPIDE);
    }

    electroaimant_eteint();

    positionChariot.file = positionFinale.file;
    positionChariot.rank = positionFinale.rank;
}

void deplaceEnDiagonalALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale, unsigned char vitesse, unsigned char aimante)
{
    unsigned int deplacementEnSteps = abs((int)((positionFinale.file - positionInitiale.file) * NBRE_DE_STEP_DANS_UNE_DEMI_CASE * COEFFICIENT_DIAGONALE));

    if(aimante == ELECTROAIMANT_ACTIF)
    {
        electroaimant_active();
    }

    if (positionInitiale.file > positionFinale.file && positionInitiale.rank > positionFinale.rank)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementEnSteps, H8_TO_A1, vitesse );
    } 
    else if (positionInitiale.file > positionFinale.file && positionInitiale.rank < positionFinale.rank) 
    {
        coreXY_deplaceEnNombreDeSteps(deplacementEnSteps, H1_TO_A8, vitesse);
    }
        
    else if (positionInitiale.file < positionFinale.file && positionInitiale.rank > positionFinale.rank)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementEnSteps, A8_TO_H1, vitesse);
    } 
        
    else if (positionInitiale.file < positionFinale.file && positionInitiale.rank < positionFinale.rank)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementEnSteps, A1_TO_H8, vitesse);
    }        

    electroaimant_eteint();

    positionChariot.file = positionFinale.file;
    positionChariot.rank = positionFinale.rank;
}

void deplaceCavalierALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale)
{

    unsigned int deplacementX, deplacementY, deplacementXenSteps, deplacementYenSteps;

    deplacementX = abs(positionFinale.file - positionInitiale.file);
    deplacementY = abs(positionFinale.rank - positionInitiale.rank);
    deplacementXenSteps = deplacementX * NBRE_DE_STEP_DANS_UNE_DEMI_CASE;
    deplacementYenSteps = deplacementY * NBRE_DE_STEP_DANS_UNE_DEMI_CASE;

    electroaimant_active();

    if (deplacementY == 4) 
    {
        if (positionInitiale.file < positionFinale.file) 
        {
            coreXY_deplaceEnNombreDeSteps(deplacementXenSteps * 0.5, A_TO_H, VITESSE_LENTE);
            if (positionInitiale.rank < positionFinale.rank)
            {
                coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _1_TO_8, VITESSE_LENTE); 
            }                
            else
            {
                coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _8_TO_1, VITESSE_LENTE);    
            }                
            coreXY_deplaceEnNombreDeSteps(deplacementXenSteps * 0.5, A_TO_H, VITESSE_LENTE);
        }
        else if (positionInitiale.file > positionFinale.file) 
        {
            coreXY_deplaceEnNombreDeSteps(deplacementXenSteps * 0.5, H_TO_A, VITESSE_LENTE);
            if (positionInitiale.rank < positionFinale.rank)
            {
                coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _1_TO_8, VITESSE_LENTE); 
            }                
            else
            {
                coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _8_TO_1, VITESSE_LENTE);    
            }                
            coreXY_deplaceEnNombreDeSteps(deplacementXenSteps * 0.5, H_TO_A, VITESSE_LENTE);
        }
    }
    else if (deplacementX == 4) 
    {
        if (positionInitiale.rank < positionFinale.rank) 
        {
            coreXY_deplaceEnNombreDeSteps(deplacementYenSteps * 0.5, _1_TO_8, VITESSE_LENTE);
            if (positionInitiale.file < positionFinale.file) 
            {
                coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, A_TO_H, VITESSE_LENTE);
            }
            else
            {
                coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, A_TO_H, VITESSE_LENTE);
            } 
            coreXY_deplaceEnNombreDeSteps(deplacementYenSteps * 0.5, _1_TO_8, VITESSE_LENTE);
        }
        else if (positionInitiale.rank > positionFinale.rank) 
        {
            coreXY_deplaceEnNombreDeSteps(deplacementYenSteps * 0.5, _8_TO_1, VITESSE_LENTE);
            if (positionInitiale.file < positionFinale.file) 
            {
                coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, A_TO_H, VITESSE_LENTE);
            }
            else
            {
                coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, A_TO_H, VITESSE_LENTE);
            } 
            coreXY_deplaceEnNombreDeSteps(deplacementYenSteps * 0.5, _8_TO_1, VITESSE_LENTE);
        }
    }

    electroaimant_eteint();

    positionChariot.file = positionFinale.file;
    positionChariot.rank = positionFinale.rank;
}

void deplaceRoqueCourtBlanc()
{
    //Déplace roi à position temporaire
    electroaimant_active();    
    coreXY_deplaceEnNombreDeSteps(2 * NBRE_DE_STEP_DANS_UNE_CASE, A_TO_H , VITESSE_LENTE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, VITESSE_LENTE);

    //Chariot à la position de la tour
    electroaimant_eteint();
    coreXY_deplaceEnNombreDeSteps(1 * NBRE_DE_STEP_DANS_UNE_CASE, A_TO_H, VITESSE_RAPIDE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, VITESSE_RAPIDE);

    //Déplace tour à la position finale
    electroaimant_active();
    coreXY_deplaceEnNombreDeSteps(2 * NBRE_DE_STEP_DANS_UNE_CASE, H_TO_A, VITESSE_LENTE);

    //Chariot à la position temporaire du roi
    electroaimant_eteint();
    coreXY_deplaceEnNombreDeSteps(1 * NBRE_DE_STEP_DANS_UNE_CASE, A_TO_H , VITESSE_RAPIDE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, VITESSE_RAPIDE);

    //Déplace roi à position finale
    electroaimant_active();
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, VITESSE_LENTE);

    electroaimant_eteint();

    positionChariot.file = 13;
    positionChariot.rank = 1;
}

void deplaceRoqueLongBlanc()
{
    //Déplace roi à position temporaire
    electroaimant_active();    
    coreXY_deplaceEnNombreDeSteps(2 * NBRE_DE_STEP_DANS_UNE_CASE, H_TO_A , VITESSE_LENTE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, VITESSE_LENTE);

    //Chariot à la position de la tour
    electroaimant_eteint();
    coreXY_deplaceEnNombreDeSteps(2 * NBRE_DE_STEP_DANS_UNE_CASE, H_TO_A, VITESSE_RAPIDE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, VITESSE_RAPIDE);

    //Déplace tour à la position finale
    electroaimant_active();
    coreXY_deplaceEnNombreDeSteps(3 * NBRE_DE_STEP_DANS_UNE_CASE, A_TO_H, VITESSE_LENTE);

    //Chariot à la position temporaire du roi
    electroaimant_eteint();
    coreXY_deplaceEnNombreDeSteps(1 * NBRE_DE_STEP_DANS_UNE_CASE, H_TO_A , VITESSE_RAPIDE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, VITESSE_RAPIDE);

    //Déplace roi à position finale
    electroaimant_active();
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, VITESSE_LENTE);

    electroaimant_eteint();

    positionChariot.file = 5;
    positionChariot.rank = 1;
}

void deplaceRoqueCourtNoir()
{
    //Déplace roi à position temporaire
    electroaimant_active();    
    coreXY_deplaceEnNombreDeSteps(2 * NBRE_DE_STEP_DANS_UNE_CASE, A_TO_H , VITESSE_LENTE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, VITESSE_LENTE);

    //Chariot à la position de la tour
    electroaimant_eteint();
    coreXY_deplaceEnNombreDeSteps(1 * NBRE_DE_STEP_DANS_UNE_CASE, A_TO_H, VITESSE_RAPIDE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, VITESSE_RAPIDE);

    //Déplace tour à la position finale
    electroaimant_active();
    coreXY_deplaceEnNombreDeSteps(2 * NBRE_DE_STEP_DANS_UNE_CASE, H_TO_A, VITESSE_LENTE);

    //Chariot à la position temporaire du roi
    electroaimant_eteint();
    coreXY_deplaceEnNombreDeSteps(1 * NBRE_DE_STEP_DANS_UNE_CASE, A_TO_H , VITESSE_RAPIDE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, VITESSE_RAPIDE);

    //Déplace roi à position finale
    electroaimant_active();
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, VITESSE_LENTE);

    electroaimant_eteint();

    positionChariot.file = 13;
    positionChariot.rank = 15;
}

void deplaceRoqueLongNoir()
{
    //Déplace roi à position temporaire
    electroaimant_active();    
    coreXY_deplaceEnNombreDeSteps(2 * NBRE_DE_STEP_DANS_UNE_CASE, H_TO_A , VITESSE_LENTE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, VITESSE_LENTE);

    //Chariot à la position de la tour
    electroaimant_eteint();
    coreXY_deplaceEnNombreDeSteps(2 * NBRE_DE_STEP_DANS_UNE_CASE, H_TO_A, VITESSE_RAPIDE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, VITESSE_RAPIDE);

    //Déplace tour à la position finale
    electroaimant_active();
    coreXY_deplaceEnNombreDeSteps(3 * NBRE_DE_STEP_DANS_UNE_CASE, A_TO_H, VITESSE_LENTE);

    //Chariot à la position temporaire du roi
    electroaimant_eteint();
    coreXY_deplaceEnNombreDeSteps(1 * NBRE_DE_STEP_DANS_UNE_CASE, H_TO_A , VITESSE_RAPIDE);
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, VITESSE_RAPIDE);

    //Déplace roi à position finale
    electroaimant_active();
    coreXY_deplaceEnNombreDeSteps(0.5 * NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, VITESSE_LENTE);

    electroaimant_eteint();

    positionChariot.file = 5;
    positionChariot.rank = 15;
}

void taskDeplacementPiece_prepareDeplacementAFaire()
{    
    taskDeplacementPiece_deplacementAFaire.positionDepart.file   = 2 * taskDeplacementPiece_deplacementAFaire.positionDepart.file + 1;
    taskDeplacementPiece_deplacementAFaire.positionDepart.rank   = 2 * taskDeplacementPiece_deplacementAFaire.positionDepart.rank + 1;
    taskDeplacementPiece_deplacementAFaire.positionArrivee.file  = 2 * taskDeplacementPiece_deplacementAFaire.positionArrivee.file + 1;
    taskDeplacementPiece_deplacementAFaire.positionArrivee.rank  = 2 * taskDeplacementPiece_deplacementAFaire.positionArrivee.rank + 1;
    ESP_LOGI(TAG, "DeplacementAFaire: type: %d, depart.file: %d depart.rank: %d, arrivee.file: %d, arrivee.rank: %d", 
        taskDeplacementPiece_deplacementAFaire.type,
        taskDeplacementPiece_deplacementAFaire.positionDepart.file,
        taskDeplacementPiece_deplacementAFaire.positionDepart.rank,
        taskDeplacementPiece_deplacementAFaire.positionArrivee.file,
        taskDeplacementPiece_deplacementAFaire.positionArrivee.rank );
}

//Definitions de variables publiques:
QueueHandle_t queueDeplacementPiece;
SemaphoreHandle_t semaphoreFinDeplacementPiece;
TaskHandle_t xHandleTaskDeplacementPiece = NULL;
//DEPLACEMENTPIECE deplacementPiece;



//Definitions de fonctions publiques:
void taskDeplacementPiece(void * pvParameters)
{
    coordonneeEchiquier_t positionExterieur;
    unsigned char deplacementX, deplacementY;

    positionChariot.file = CHARIOT_POSITION_INITIALE_FILE;
    positionChariot.rank = CHARIOT_POSITION_INITIALE_RANK;

    electroaimant_eteint();

    while(1)
    {
        //attend déplacement (QUEUE) (info: type, posDepart, posArrivee)
        if(xQueueReceive(queueDeplacementPiece, &taskDeplacementPiece_deplacementAFaire, portMAX_DELAY))
        {
            taskDeplacementPiece_prepareDeplacementAFaire();
            if(taskDeplacementPiece_deplacementAFaire.type == CAPTURE_A_FAIRE)
            {
                //Déplace chariot vers piece à capturer
                deplaceALaPosition( positionChariot, 
                                    taskDeplacementPiece_deplacementAFaire.positionArrivee, 
                                    VITESSE_RAPIDE, 
                                    ELECTROAIMANT_ETEINT);

                vTaskDelay(1000/portTICK_PERIOD_MS);

                    
                //Sort la piece du jeu
                if(taskDeplacementPiece_deplacementAFaire.positionArrivee.rank == 15)
                {
                    positionExterieur.rank = taskDeplacementPiece_deplacementAFaire.positionArrivee.rank - 1;
                }
                else
                {
                    positionExterieur.rank = taskDeplacementPiece_deplacementAFaire.positionArrivee.rank + 1; 
                }
                positionExterieur.file = 0;
                deplaceALaPosition( positionChariot, 
                                    positionExterieur , 
                                    VITESSE_LENTE, 
                                    ELECTROAIMANT_ACTIF); 
            }

            if(taskDeplacementPiece_deplacementAFaire.type == EN_PASSANT)
            {
                //à compléter
            }


            //Déplace chariot vers position de départ
            ESP_LOGI(TAG, "Déplace chariot vers position de départ");
            deplaceALaPosition( positionChariot, 
                                taskDeplacementPiece_deplacementAFaire.positionDepart, 
                                VITESSE_RAPIDE, 
                                ELECTROAIMANT_ETEINT);

            
            vTaskDelay(1000/portTICK_PERIOD_MS);

            //Déplace piece vers position arrivée
            if(taskDeplacementPiece_deplacementAFaire.type == NORMAL || taskDeplacementPiece_deplacementAFaire.type == EN_PASSANT ||  taskDeplacementPiece_deplacementAFaire.type == CAPTURE_A_FAIRE)
            {
                ESP_LOGI(TAG, "Déplace piece vers position arrivée");
                deplacementX = abs(taskDeplacementPiece_deplacementAFaire.positionArrivee.file - taskDeplacementPiece_deplacementAFaire.positionDepart.file);
                deplacementY = abs(taskDeplacementPiece_deplacementAFaire.positionArrivee.rank - taskDeplacementPiece_deplacementAFaire.positionDepart.rank);
                
                if(deplacementX == deplacementY)
                {
                    deplaceEnDiagonalALaPosition(   taskDeplacementPiece_deplacementAFaire.positionDepart, 
                                                    taskDeplacementPiece_deplacementAFaire.positionArrivee, 
                                                    VITESSE_LENTE, 
                                                    ELECTROAIMANT_ACTIF);
                }
                else if((deplacementX == 2 && deplacementY == 4) || 
                        (deplacementX == 4 && deplacementY == 2))
                {
                    deplaceCavalierALaPosition( taskDeplacementPiece_deplacementAFaire.positionDepart, 
                                                taskDeplacementPiece_deplacementAFaire.positionArrivee);
                }
                else
                {
                    deplaceALaPosition( taskDeplacementPiece_deplacementAFaire.positionDepart, 
                                    taskDeplacementPiece_deplacementAFaire.positionArrivee, 
                                    VITESSE_LENTE, 
                                    ELECTROAIMANT_ACTIF);
                }
                
            }
            else if(taskDeplacementPiece_deplacementAFaire.type == ROQUE_COURT_BLANC)
            {
                deplaceRoqueCourtBlanc();
            }
            else if(taskDeplacementPiece_deplacementAFaire.type == ROQUE_LONG_BLANC)
            {
                deplaceRoqueLongBlanc();
            }
            else if(taskDeplacementPiece_deplacementAFaire.type == ROQUE_COURT_NOIR)
            {
                deplaceRoqueCourtNoir();
            }
            else if(taskDeplacementPiece_deplacementAFaire.type == ROQUE_LONG_NOIR)
            {
                deplaceRoqueLongNoir();
            }

            xSemaphoreGive(semaphoreFinDeplacementPiece);
        }     
    }

    vTaskDelete(xHandleTaskDeplacementPiece);
}





void taskDeplacementPiece_initialise(void)
{
    queueDeplacementPiece = xQueueCreate(5, sizeof(taskDeplacementPiece_deplacementAFaire));
    semaphoreFinDeplacementPiece = xSemaphoreCreateBinary();

    xTaskCreatePinnedToCore(taskDeplacementPiece, 
                            "TaskDeplacementPiece", 
                            TASKDEPLACEMENTPIECE_STACK_SIZE, 
                            NULL, 
                            TASKDEPLACEMENTPIECE_PRIORITY, 
                            &xHandleTaskDeplacementPiece, 
                            TASKDEPLACEMENTPIECE_CORE
    );
}