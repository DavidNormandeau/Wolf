//taskDeplacementPiece:
//Historique: 
// 2023-05-02, David Normandeau, creation

//INCLUSIONS
#include <stdlib.h>
#include "main.h"
#include "coreXY.h"
#include "taskDeplacementPiece.h"

//Definitions privees
//static const char* TAG = "TASK DEPLACEMENT PIECE";
#define CAPTURE_A_FAIRE         0
#define DEPLACEMENT_VERS        1
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

//Definitions de variables privees:
coordonneeEchiquier_t positionChariot;

//Definitions de fonctions privees:
void deplaceALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale, unsigned char vitesse, unsigned char aimante)
{
    unsigned int deplacementXenSteps, deplacementYenSteps;

    if(aimante == ELECTROAIMANT_ACTIF)
    {
        electroaimant_active();
    }


    deplacementXenSteps = abs(positionFinale.x - positionInitiale.x) * NBRE_DE_STEP_DANS_UNE_CASE;
    deplacementYenSteps = abs(positionFinale.y - positionInitiale.y) * NBRE_DE_STEP_DANS_UNE_CASE;
    
    if(positionFinale.x > positionInitiale.x)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, A_TO_H, vitesse);
    }
    else if(positionFinale.x < positionInitiale.x)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, H_TO_A, vitesse);
    }

    if(positionFinale.y > positionInitiale.y)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _1_TO_8, VITESSE_RAPIDE);
    }
    else if(positionFinale.y < positionInitiale.y)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _8_TO_1, VITESSE_RAPIDE);
    }

    electroaimant_eteint();

    positionChariot.x = positionFinale.x;
    positionChariot.y = positionFinale.y;
}

void deplaceEnDiagonalALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale, unsigned char vitesse, unsigned char aimante)
{
    unsigned int deplacementEnSteps = abs(positionFinale.x - positionInitiale.x) * NBRE_DE_STEP_DANS_UNE_CASE * COEFFICIENT_DIAGONALE;

    if(aimante == ELECTROAIMANT_ACTIF)
    {
        electroaimant_active();
    }

    if (positionInitiale.x > positionFinale.x && positionInitiale.y > positionFinale.y)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementEnSteps, H8_TO_A1, vitesse );
    } 
    else if (positionInitiale.x > positionFinale.x && positionInitiale.y < positionFinale.y) 
    {
        coreXY_deplaceEnNombreDeSteps(deplacementEnSteps, H1_TO_A8, vitesse);
    }
        
    else if (positionInitiale.x < positionFinale.x && positionInitiale.y > positionFinale.y)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementEnSteps, A8_TO_H1, vitesse);
    } 
        
    else if (positionInitiale.x < positionFinale.x && positionInitiale.y < positionFinale.y)
    {
        coreXY_deplaceEnNombreDeSteps(deplacementEnSteps, A1_TO_H8, vitesse);
    }        

    electroaimant_eteint();

    positionChariot.x = positionFinale.x;
    positionChariot.y = positionFinale.y;
}

void deplaceCavalierALaPosition(coordonneeEchiquier_t positionInitiale, coordonneeEchiquier_t positionFinale)
{

    unsigned int deplacementX, deplacementY, deplacementXenSteps, deplacementYenSteps;

    deplacementX = abs(positionFinale.x - positionInitiale.x);
    deplacementY = abs(positionFinale.y - positionInitiale.y);
    deplacementXenSteps = deplacementX * NBRE_DE_STEP_DANS_UNE_CASE;
    deplacementYenSteps = deplacementY * NBRE_DE_STEP_DANS_UNE_CASE;

    electroaimant_active();

    if (deplacementY == 2) 
    {
        if (positionInitiale.x < positionFinale.x) 
        {
            coreXY_deplaceEnNombreDeSteps(deplacementXenSteps * 0.5, A_TO_H, VITESSE_LENTE);
            if (positionInitiale.y < positionFinale.y)
            {
                coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _1_TO_8, VITESSE_LENTE); 
            }                
            else
            {
                coreXY_deplaceEnNombreDeSteps(deplacementYenSteps, _8_TO_1, VITESSE_LENTE);    
            }                
            coreXY_deplaceEnNombreDeSteps(deplacementXenSteps * 0.5, A_TO_H, VITESSE_LENTE);
        }
        else if (positionInitiale.x > positionFinale.x) 
        {
            coreXY_deplaceEnNombreDeSteps(deplacementXenSteps * 0.5, H_TO_A, VITESSE_LENTE);
            if (positionInitiale.y < positionFinale.y)
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
    else if (deplacementX == 2) 
    {
        if (positionInitiale.y < positionFinale.y) 
        {
            coreXY_deplaceEnNombreDeSteps(deplacementYenSteps * 0.5, _1_TO_8, VITESSE_LENTE);
            if (positionInitiale.x < positionFinale.x) 
            {
                coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, A_TO_H, VITESSE_LENTE);
            }
            else
            {
                coreXY_deplaceEnNombreDeSteps(deplacementXenSteps, A_TO_H, VITESSE_LENTE);
            } 
            coreXY_deplaceEnNombreDeSteps(deplacementYenSteps * 0.5, _1_TO_8, VITESSE_LENTE);
        }
        else if (positionInitiale.y > positionFinale.y) 
        {
            coreXY_deplaceEnNombreDeSteps(deplacementYenSteps * 0.5, _8_TO_1, VITESSE_LENTE);
            if (positionInitiale.x < positionFinale.x) 
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

    positionChariot.x = positionFinale.x;
    positionChariot.y = positionFinale.y;
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

    positionChariot.x = 7;
    positionChariot.y = 1;
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

    positionChariot.x = 3;
    positionChariot.y = 1;
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

    positionChariot.x = 7;
    positionChariot.y = 8;
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

    positionChariot.x = 3;
    positionChariot.y = 8;
}

//Definitions de variables publiques:
TaskHandle_t xHandleTaskDeplacementPiece = NULL;


//Definitions de fonctions publiques:
int taskDeplacementPiece()
{
    coordonneeEchiquier_t positionChariot = {CHARIOT_POSITION_INITIALE_X, CHARIOT_POSITION_INITIALE_Y};
    coordonneeEchiquier_t positionTemp;
    coordonneeEchiquier_t positionExterieur;
    info_deplacement_t deplacementAFaire;
    unsigned char deplacementX, deplacementY;


    electroaimant_eteint();
    while(1)
    {
        //attend déplacement (QUEUE) (info: type, posDepart, posArrivee)
        if(xQueueReceive(queueDeplacementPiece, &deplacementAFaire, portMAX_DELAY))
        {
            if(deplacementAFaire.type == CAPTURE_A_FAIRE)
            {
                //Déplace chariot vers piece à capturer
                deplaceALaPosition( positionChariot, 
                                    deplacementAFaire.positionArrivee, 
                                    VITESSE_RAPIDE, 
                                    ELECTROAIMANT_ETEINT);

                    
                //Sort la piece du jeu
                if(deplacementAFaire.positionArrivee.y == 8)
                {
                    positionExterieur.y = deplacementAFaire.positionArrivee.y - 0.5;
                }
                else
                {
                    positionExterieur.y = deplacementAFaire.positionArrivee.y + 0.5; 
                }
                positionExterieur.x = 0;
                deplaceALaPosition( positionTemp, 
                                    positionExterieur , 
                                    VITESSE_LENTE, 
                                    ELECTROAIMANT_ACTIF); 
            }

            if(deplacementAFaire.type == EN_PASSANT)
            {
                //à compléter
            }

            //Déplace chariot vers position de départ
            deplaceALaPosition( positionChariot, 
                                deplacementAFaire.positionDepart , 
                                VITESSE_RAPIDE, 
                                ELECTROAIMANT_ETEINT);

            //Déplace piece vers position arrivée
            if(deplacementAFaire.type == NORMAL || deplacementAFaire.type == EN_PASSANT)
            {
                deplacementX = abs(deplacementAFaire.positionArrivee.x - deplacementAFaire.positionDepart.x);
                deplacementY = abs(deplacementAFaire.positionArrivee.y - deplacementAFaire.positionDepart.y);
                
                if(deplacementX == deplacementY)
                {
                    deplaceEnDiagonalALaPosition(   deplacementAFaire.positionDepart, 
                                                    deplacementAFaire.positionArrivee, 
                                                    VITESSE_LENTE, 
                                                    ELECTROAIMANT_ACTIF);
                }
                else if((deplacementX == 1 && deplacementY == 2) || 
                        (deplacementX == 2 && deplacementY == 1))
                {
                    deplaceCavalierALaPosition( deplacementAFaire.positionDepart, 
                                                deplacementAFaire.positionArrivee);
                }
                else
                {
                    deplaceALaPosition( deplacementAFaire.positionDepart, 
                                    deplacementAFaire.positionArrivee, 
                                    VITESSE_LENTE, 
                                    ELECTROAIMANT_ACTIF);
                }
                
            }
            else if(deplacementAFaire.type == ROQUE_COURT_BLAMC)
            {
                deplaceRoqueCourtBlanc();
            }
            else if(deplacementAFaire.type == ROQUE_LONG_BLANC)
            {
                deplaceRoqueLongBlanc();
            }
            else if(deplacementAFaire.type == ROQUE_COURT_NOIR)
            {
                deplaceRoqueCourtNoir();
            }
            else if(deplacementAFaire.type == ROQUE_LONG_NOIR)
            {
                deplaceRoqueLongNoir();
            }
        }     
    }

    vTaskDelete(xHandleTaskDeplacementPiece);
}





void taskDeplacementPiece_initialise(void)
{
    xTaskCreatePinnedToCore(taskDeplacementPiece, 
                            "TaskDeplacementPiece", 
                            TASKDEPLACEMENTPIECE_STACK_SIZE, 
                            NULL, 
                            TASKDEPLACEMENTPIECE_PRIORITY, 
                            &xHandleTaskDeplacementPiece, 
                            TASKDEPLACEMENTPIECE_CORE
    );


    positionChariot = {CHARIOT_POSITION_INITIALE_X, CHARIOT_POSITION_INITIALE_Y};
}