//piloteMoteurDroit:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "driver/gpio.h"
#include "define.h"
#include "piloteMoteurDroit.h"

//Definitions privees
//  static const char* TAG = "PILOTEMOTEURDROIT";
#define ENABLE_MOTEUR   0
#define DISABLE_MOTEUR  1

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void piloteMoteurDroit_metDirA(unsigned char valeur)
{
    gpio_set_level(PILOTEMOTEURDROIT_DIR_PIN, valeur);
}

void piloteMoteurDroit_metStepA(unsigned char valeur)
{
    gpio_set_level(PILOTEMOTEURDROIT_STEP_PIN, valeur);
}

void piloteMoteurDroit_enable(void)
{
    gpio_set_level(PILOTEMOTEURDROIT_ENABLE_PIN, ENABLE_MOTEUR);
}

void piloteMoteurDroit_disable(void)
{
    gpio_set_level(PILOTEMOTEURDROIT_ENABLE_PIN, DISABLE_MOTEUR);
}


void piloteMoteurDroit_initialise(void)
{
    gpio_config_t conf = {
        .pin_bit_mask = ((1ULL<<PILOTEMOTEURDROIT_DIR_PIN) | (1ULL<<PILOTEMOTEURDROIT_STEP_PIN) | (1ULL<<PILOTEMOTEURDROIT_ENABLE_PIN)),               
        .mode = GPIO_MODE_OUTPUT,                  
        .pull_up_en = GPIO_PULLUP_DISABLE,          
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       
        .intr_type = GPIO_INTR_DISABLE 
    };
    gpio_config(&conf);
}