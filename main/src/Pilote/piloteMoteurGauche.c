//piloteMoteurGauche:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "driver/gpio.h"
#include "main.h"
#include "piloteMoteurGauche.h"

//Definitions privees
//  static const char* TAG = "PILOTEMOTEURGAUCHE";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void piloteMoteurGauche_metDirA(unsigned char valeur)
{
    gpio_set_level(PILOTEMOTEURGAUCHE_DIR_PIN, valeur);
}

void piloteMoteurGauche_metStepA(unsigned char valeur)
{
    gpio_set_level(PILOTEMOTEURGAUCHE_STEP_PIN, valeur);
}


void piloteMoteurGauche_initialise(void)
{
    gpio_config_t conf = {
        .pin_bit_mask = ((1ULL<<PILOTEMOTEURGAUCHE_DIR_PIN) | (1ULL<<PILOTEMOTEURGAUCHE_STEP_PIN)),               
        .mode = GPIO_MODE_OUTPUT,                  
        .pull_up_en = GPIO_PULLUP_DISABLE,          
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       
        .intr_type = GPIO_INTR_DISABLE 
    };
    gpio_config(&conf);
}