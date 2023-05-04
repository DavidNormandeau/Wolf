#ifndef PILOTEUART2_H
#define PILOTEUART2_H

//MODULE: piloteUart2
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "define.h")
// #define PILOTEUART2_TX_PIN        GPIO_NUM_17
// #define PILOTEUART2_RX_PIN        GPIO_NUM_16




//Dependances logicielles
//(copiez et adaptez ce qui suit dans "define.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
int piloteUart2_transmetMessage(char*, size_t);
int piloteUart2_recoitMessage(char*, uint32_t);
esp_err_t piloteUart2_termine();
esp_err_t piloteUart2_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif