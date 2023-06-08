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
void main_test();

//Definitions de variables publiques:
unsigned char tabPieceDetecteeSurEchiquier[8][8];
coordonneeEchiquier_t positionChariot;


//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void app_main(void)
{
    main_initialise();  

    ESP_LOGI(TAG, "Task, Queue and Semaphore created!");  

    while(1)
    {                
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // main_test();        
    }
}



void main_initialise()
{
    piloteDetectionPiece_initialise();
    piloteElectroaimant_initialise();
    piloteLimitSwitchX_initialise();
    piloteLimitSwitchY_initialise();
    piloteMoteurGauche_initialise();
    piloteMoteurDroit_initialise();
    piloteUart2_initialise();    
    detectionPiece_initialise();
    electroaimant_initialise();
    coreXY_initialise();
    taskTxUart_initialise();
    taskRxUart_initialise();
    taskCalibration_initialise();
    taskDeplacementPiece_initialise();
    taskGestionControleur1_initialise();
}

void main_test()
{
    //Test coreXY
        // ESP_LOGI(TAG, "H1 to A8");
        // coreXY_deplaceEnNombreDeSteps(500, H1_TO_A8, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "8 to 1");
        // coreXY_deplaceEnNombreDeSteps(3*NBRE_DE_STEP_DANS_UNE_CASE, _8_TO_1, 3);
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
        // coreXY_deplaceEnNombreDeSteps(3*NBRE_DE_STEP_DANS_UNE_CASE, _1_TO_8, 3);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "H8 to A1");
        // coreXY_deplaceEnNombreDeSteps(500, H8_TO_A1, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);
        // ESP_LOGI(TAG, "A to H");        
        // coreXY_deplaceEnNombreDeSteps(500, A_TO_H, 1);
        // vTaskDelay(1000/portTICK_PERIOD_MS);

        //TEST detection Int64
        // int i, j;
        // detectionPiece_litLEchiquierInt64(&pieceDetecteeSurEchiquier.entier64);
        // printf("---------------------------------\r\n");
        // for(i = 7; i >= 0; i--)
        // {
        //     for(j = 0; j < 8; j++)
        //     {
        //         printf("| %d ", !!((pieceDetecteeSurEchiquier.cTab[i] << j) & 0x80));

        //     } 
        //     printf("|\r\n---------------------------------\r\n");   

        // }
        // printf("|\r\n\r\n\r\n");

        //TEST detection
        // int i;
        // detectionPiece_litLEchiquier(tabPieceDetecteeSurEchiquier);

        // printf("---------------------------------\r\n");
        // for(i = 0; i < 64; i++)
        // {
        //     if(i % 8 == 0 && i != 0)
        //     {
        //       printf("|\r\n---------------------------------\r\n");  
        //     }
        //     printf("| %d ", tabPieceDetecteeSurEchiquier[i]);            
        // }
        // printf("|\r\n\r\n\r\n");

        //TEST detection 8x8
        // int rank, file;
        // detectionPiece_litLEchiquier8x8(tabPieceDetecteeSurEchiquier);

        // printf("---------------------------------\r\n");
        // for(rank = RANK_1; rank <= RANK_8; rank++)
        // {
        //     for(file = FILE_A; file <= FILE_H; file++)
        //     {
        //         printf("| %d ", tabPieceDetecteeSurEchiquier[file][rank]); 
        //     }
        //     printf("|\r\n---------------------------------\r\n");  
           
        // }
        // printf("\r\n\r\n\r\n");

        // printf("H1: %d  ", detectionPiece_litLaCase(H1));
        // printf("H2: %d  ", detectionPiece_litLaCase(H2));
        // printf("H3: %d  ", detectionPiece_litLaCase(H3));
        // printf("H4: %d  ", detectionPiece_litLaCase(H4));
        // printf("H5: %d  ", detectionPiece_litLaCase(H5));
        // printf("H6: %d  ", detectionPiece_litLaCase(H6));
        // printf("H7: %d  ", detectionPiece_litLaCase(H7));
        // printf("H8: %d  \n", detectionPiece_litLaCase(H8));
        // printf("G1: %d  ", detectionPiece_litLaCase(G1));
        // printf("G2: %d  ", detectionPiece_litLaCase(G2));
        // printf("G3: %d  ", detectionPiece_litLaCase(G3));
        // printf("G4: %d  ", detectionPiece_litLaCase(G4));
        // printf("G5: %d  ", detectionPiece_litLaCase(G5));
        // printf("G6: %d  ", detectionPiece_litLaCase(G6));
        // printf("G7: %d  ", detectionPiece_litLaCase(G7));
        // printf("G8: %d  \n", detectionPiece_litLaCase(G8));
        // printf("F1: %d  ", detectionPiece_litLaCase(F1));
        // printf("F2: %d  ", detectionPiece_litLaCase(F2));
        // printf("F3: %d  ", detectionPiece_litLaCase(F3));
        // printf("F4: %d  ", detectionPiece_litLaCase(F4));
        // printf("F5: %d  ", detectionPiece_litLaCase(F5));
        // printf("F6: %d  ", detectionPiece_litLaCase(F6));
        // printf("F7: %d  ", detectionPiece_litLaCase(F7));
        // printf("F8: %d  \n", detectionPiece_litLaCase(F8));
        // printf("E1: %d  ", detectionPiece_litLaCase(E1));
        // printf("E2: %d  ", detectionPiece_litLaCase(E2));
        // printf("E3: %d  ", detectionPiece_litLaCase(E3));
        // printf("E4: %d  ", detectionPiece_litLaCase(E4));
        // printf("E5: %d  ", detectionPiece_litLaCase(E5));
        // printf("E6: %d  ", detectionPiece_litLaCase(E6));
        // printf("E7: %d  ", detectionPiece_litLaCase(E7));
        // printf("E8: %d  \n", detectionPiece_litLaCase(E8));
        // printf("D1: %d  ", detectionPiece_litLaCase(D1));
        // printf("D2: %d  ", detectionPiece_litLaCase(D2));
        // printf("D3: %d  ", detectionPiece_litLaCase(D3));
        // printf("D4: %d  ", detectionPiece_litLaCase(D4));
        // printf("D5: %d  ", detectionPiece_litLaCase(D5));
        // printf("D6: %d  ", detectionPiece_litLaCase(D6));
        // printf("D7: %d  ", detectionPiece_litLaCase(D7));
        // printf("D8: %d  \n", detectionPiece_litLaCase(D8));
        // printf("C1: %d  ", detectionPiece_litLaCase(C1));
        // printf("C2: %d  ", detectionPiece_litLaCase(C2));
        // printf("C3: %d  ", detectionPiece_litLaCase(C3));
        // printf("C4: %d  ", detectionPiece_litLaCase(C4));
        // printf("C5: %d  ", detectionPiece_litLaCase(C5));
        // printf("C6: %d  ", detectionPiece_litLaCase(C6));
        // printf("C7: %d  ", detectionPiece_litLaCase(C7));
        // printf("C8: %d  \n", detectionPiece_litLaCase(C8));
        // printf("B1: %d  ", detectionPiece_litLaCase(B1));
        // printf("B2: %d  ", detectionPiece_litLaCase(B2));
        // printf("B3: %d  ", detectionPiece_litLaCase(B3));
        // printf("B4: %d  ", detectionPiece_litLaCase(B4));
        // printf("B5: %d  ", detectionPiece_litLaCase(B5));
        // printf("B6: %d  ", detectionPiece_litLaCase(B6));
        // printf("B7: %d  ", detectionPiece_litLaCase(B7));
        // printf("B8: %d  \n", detectionPiece_litLaCase(B8));
        // printf("A1: %d  ", detectionPiece_litLaCase(A1));
        // printf("A2: %d  ", detectionPiece_litLaCase(A2));
        // printf("A3: %d  ", detectionPiece_litLaCase(A3));
        // printf("A4: %d  ", detectionPiece_litLaCase(A4));
        // printf("A5: %d  ", detectionPiece_litLaCase(A5));
        // printf("A6: %d  ", detectionPiece_litLaCase(A6));
        // printf("A7: %d  ", detectionPiece_litLaCase(A7));
        // printf("A8: %d  \n", detectionPiece_litLaCase(A8));
}


