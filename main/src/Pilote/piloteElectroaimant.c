//piloteElectroaimant:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "driver/gpio.h"
#include "main.h"
#include "piloteElectroaimant.h"

//Definitions privees
//  static const char* TAG = "PILOTEELECTROAIMANT";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void piloteElectroaimant_metLaSortieA(unsigned char valeur)
{
    gpio_set_level(PILOTEELECTROAIMANT_PIN, valeur);
}


void piloteElectroaimant_initialise(void)
{
    gpio_config_t conf = {
        .pin_bit_mask = (1ULL<<PILOTEELECTROAIMANT_PIN),               
        .mode = GPIO_MODE_OUTPUT,                  
        .pull_up_en = GPIO_PULLUP_DISABLE,          
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       
        .intr_type = GPIO_INTR_DISABLE 
    };
    gpio_config(&conf);
}