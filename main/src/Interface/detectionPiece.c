//detectionPiece:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "main.h"
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

    return piloteDetectionPiece_litCOM();
}

void detectionPiece_litLEchiquier(unsigned char* echiquier)
{
    unsigned char i;
    for(i = A1; i <= H8; i++)
    {
        echiquier[i] = detectionPiece_litLaCase(i);
    }
}

void detectionPiece_initialise(void)
{
    piloteDetectionPiece_metEN1_2A(DISABLE_MUX);
    piloteDetectionPiece_metEN3_4A(DISABLE_MUX);
    piloteDetectionPiece_metEN5_6A(DISABLE_MUX);
    piloteDetectionPiece_metEN7_8A(DISABLE_MUX);    
}
