//piloteMoteurGauche:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "driver/gpio.h"
#include "define.h"
#include "piloteMoteurGauche.h"

//Definitions privees
//  static const char* TAG = "PILOTEMOTEURGAUCHE";
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
void piloteMoteurGauche_metDirA(unsigned char valeur)
{
    gpio_set_level(PILOTEMOTEURGAUCHE_DIR_PIN, valeur);
}

void piloteMoteurGauche_metStepA(unsigned char valeur)
{
    gpio_set_level(PILOTEMOTEURGAUCHE_STEP_PIN, valeur);
}

void piloteMoteurGauche_enable(void)
{
    gpio_set_level(PILOTEMOTEURGAUCHE_ENABLE_PIN, ENABLE_MOTEUR);
}

void piloteMoteurGauche_disable(void)
{
    gpio_set_level(PILOTEMOTEURGAUCHE_ENABLE_PIN, DISABLE_MOTEUR);
}


void piloteMoteurGauche_initialise(void)
{
    gpio_config_t conf = {
        .pin_bit_mask = ((1ULL<<PILOTEMOTEURGAUCHE_DIR_PIN) | (1ULL<<PILOTEMOTEURGAUCHE_STEP_PIN) | (1ULL<<PILOTEMOTEURGAUCHE_ENABLE_PIN)),               
        .mode = GPIO_MODE_OUTPUT,                  
        .pull_up_en = GPIO_PULLUP_DISABLE,          
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       
        .intr_type = GPIO_INTR_DISABLE 
    };
    gpio_config(&conf);
}