//piloteDetectionPiece:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "main.h"
#include "piloteDetectionPiece.h"

//Definitions privees
 static const char* TAG = "PILOTEDETECTIONPIECE";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void piloteDetectionPiece_metS0A(unsigned char valeur)
{
    gpio_set_level(PILOTEPIECEDETECTION_S0_PIN, valeur);
}

void piloteDetectionPiece_metS1A(unsigned char valeur)
{
    gpio_set_level(PILOTEPIECEDETECTION_S1_PIN, valeur);
}

void piloteDetectionPiece_metS2A(unsigned char valeur)
{
    gpio_set_level(PILOTEPIECEDETECTION_S2_PIN, valeur);
}

void piloteDetectionPiece_metS3A(unsigned char valeur)
{
    gpio_set_level(PILOTEPIECEDETECTION_S3_PIN, valeur);
}

void piloteDetectionPiece_metEN1_2A(unsigned char valeur)
{
    gpio_set_level(PILOTEPIECEDETECTION_EN1_2_PIN, valeur);
}

void piloteDetectionPiece_metEN3_4A(unsigned char valeur)
{
    gpio_set_level(PILOTEPIECEDETECTION_EN3_4_PIN, valeur);
}

void piloteDetectionPiece_metEN5_6A(unsigned char valeur)
{
    gpio_set_level(PILOTEPIECEDETECTION_EN5_6_PIN, valeur);
}

void piloteDetectionPiece_metEN7_8A(unsigned char valeur)
{
    gpio_set_level(PILOTEPIECEDETECTION_EN7_8_PIN, valeur);
}

unsigned char piloteDetectionPiece_litCOM(void)
{
    return gpio_get_level(PILOTEPIECEDETECTION_COM_PIN);
}

void piloteDetectionPiece_initialise(void)
{
    //output pins
    gpio_config_t conf = {
        .pin_bit_mask = ((1ULL<<PILOTEPIECEDETECTION_S0_PIN) | (1ULL<<PILOTEPIECEDETECTION_S1_PIN) | 
                        (1ULL<<PILOTEPIECEDETECTION_S2_PIN) | (1ULL<<PILOTEPIECEDETECTION_S3_PIN) | 
                        (1ULL<<PILOTEPIECEDETECTION_EN1_2_PIN) | (1ULL<<PILOTEPIECEDETECTION_EN3_4_PIN) | 
                        (1ULL<<PILOTEPIECEDETECTION_EN5_6_PIN) | (1ULL<<PILOTEPIECEDETECTION_EN7_8_PIN)),               
        .mode = GPIO_MODE_OUTPUT,                  
        .pull_up_en = GPIO_PULLUP_DISABLE,          
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       
        .intr_type = GPIO_INTR_DISABLE 
    };
    gpio_config(&conf);

    //input pins
    conf.pin_bit_mask = (1ULL<<PILOTEPIECEDETECTION_COM_PIN);
    conf.mode = GPIO_MODE_INPUT;
    gpio_config(&conf);  
}