//piloteLimitSwitchX:
//Historique: 
// 2023-03-30, David Normandeau, creation

//INCLUSIONS
#include "driver/gpio.h"
#include "define.h"
#include "piloteLimitSwitchX.h"

//Definitions privees
//static const char* TAG = "PILOTELIMITSWITCH";

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
unsigned char piloteLimitSwitchX_litLEntree(void)
{
    return gpio_get_level(PILOTELIMITSWITCHX_PIN);
}

void piloteLimitSwitchX_initialise(void)
{
    gpio_config_t conf = {
        .pin_bit_mask = (1ULL<<PILOTELIMITSWITCHX_PIN),               
        .mode = GPIO_MODE_INPUT,                  
        .pull_up_en = GPIO_PULLUP_DISABLE,          
        .pull_down_en = GPIO_PULLDOWN_DISABLE,       
        .intr_type = GPIO_INTR_NEGEDGE              
    };
    gpio_config(&conf); 
}