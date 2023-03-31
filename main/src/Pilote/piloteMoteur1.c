//piloteMoteur1:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "driver/gpio.h"
#include "main.h"
#include "piloteMoteur1.h"

//Definitions privees
//  static const char* TAG = "PILOTEMOTEUR1";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void piloteMoteur1_metDirA(unsigned char valeur)
{
    gpio_set_level(PILOTEMOTEUR1_DIR_PIN, valeur);
}

void piloteMoteur1_metStepA(unsigned char valeur)
{
    gpio_set_level(PILOTEMOTEUR1_STEP_PIN, valeur);
}


void piloteMoteur1_initialise(void)
{
    gpio_config_t conf = {
        .pin_bit_mask = ((1ULL<<PILOTEMOTEUR1_DIR_PIN) | (1ULL<<PILOTEMOTEUR1_STEP_PIN)),               
        .mode = GPIO_MODE_OUTPUT,                  
        .pull_up_en = GPIO_PULLUP_DISABLE,          
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       
        .intr_type = GPIO_INTR_DISABLE 
    };
    gpio_config(&conf);
}