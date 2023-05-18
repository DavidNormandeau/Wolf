//detectionPiece:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteDetectionPiece.h"
#include "detectionPiece.h"

//Definitions privees
static const char* TAG = "DETECTION PIECE";
#define ENABLE_MUX    0
#define DISABLE_MUX   1 

#define ERREUR_CASE_INVALID 2

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
unsigned char detectionPiece_litLaCase(case_t caseALire)
{
    if( caseALire >= 64 )
    {
        ESP_LOGE(TAG, "Case invalide!");
        return ERREUR_CASE_INVALID;
    }

    piloteDetectionPiece_metS0A(caseALire & 0x01);
    piloteDetectionPiece_metS1A((caseALire & 0x02) >> 1);
    piloteDetectionPiece_metS2A((caseALire & 0x04) >> 2);
    piloteDetectionPiece_metS3A((caseALire & 0x08) >> 3);

    piloteDetectionPiece_metEN1_2A(DISABLE_MUX);
    piloteDetectionPiece_metEN3_4A(DISABLE_MUX);
    piloteDetectionPiece_metEN5_6A(DISABLE_MUX);
    piloteDetectionPiece_metEN7_8A(DISABLE_MUX);

    if(caseALire < 16)
    {
        piloteDetectionPiece_metEN1_2A(ENABLE_MUX);
    }
    else if(caseALire < 32)
    {
        piloteDetectionPiece_metEN3_4A(ENABLE_MUX);
    }
    else if( caseALire < 48)
    {
        piloteDetectionPiece_metEN5_6A(ENABLE_MUX);
    }
    else
    {
        piloteDetectionPiece_metEN7_8A(ENABLE_MUX);
    }

    
    vTaskDelay(1); //à modifier pour meilleur performance

    return piloteDetectionPiece_litCOM();
}

// void detectionPiece_litLEchiquier(unsigned char* echiquier)
// {
//     unsigned char i;
//     for(i = A1; i <= H8; i++)
//     {
//         echiquier[i] = detectionPiece_litLaCase(i);
//     }
// }

void detectionPiece_litLEchiquier8x8(unsigned char echiquier[8][8])
{
    signed char file, rank, n = 0; //n est pour compenser que le file est à l'envers

    ESP_LOGI(TAG, "START");
    for(rank = 0; rank < 8; rank++)
    {
        for(file = 7; file >= 0; file--)
        {
            echiquier[file][rank] = detectionPiece_litLaCase(n);
            n++;
        }
        
    }
    ESP_LOGI(TAG, "END");
}

void detectionPiece_litLEchiquierInt64(uint64_t* echiquier)
{
    unsigned char i;
    *echiquier = 0;
    for(i = A1; i <= H8; i++)
    {
        *echiquier = *echiquier << 1;
        *echiquier = *echiquier | detectionPiece_litLaCase(i);
    }
    ESP_LOGI(TAG, "0x%08llX", *echiquier);
}

void detectionPiece_initialise(void)
{
    piloteDetectionPiece_metEN1_2A(DISABLE_MUX);
    piloteDetectionPiece_metEN3_4A(DISABLE_MUX);
    piloteDetectionPiece_metEN5_6A(DISABLE_MUX);
    piloteDetectionPiece_metEN7_8A(DISABLE_MUX);    
}
