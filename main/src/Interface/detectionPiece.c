//detectionPiece:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "main.h"
#include "detectionPiece.h"

//Definitions privees
static const char* TAG = "DETECTION PIECE";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void detectionPiece_litLaCase(unsigned char coordonnee)
{
    if( coordonnee >= 64 )
    {
        ESP_LOGE(TAG, "Case invalide!");
        return ;
    }

    // gpio_set_level(PILOTEDETECTIONPIECE_S0_PIN, (valeur & 0x01));
    // gpio_set_level(PILOTEDETECTIONPIECE_S1_PIN, (valeur & 0x02) >> 1);
    // gpio_set_level(PILOTEDETECTIONPIECE_S2_PIN, (valeur & 0x04) >> 2);
    // gpio_set_level(PILOTEDETECTIONPIECE_S3_PIN, (valeur & 0x08) >> 3);

}

void detectionPiece_initialise(void)
{
 
}
