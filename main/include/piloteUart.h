#ifndef PILOTEUART_H
#define PILOTEUART_H

//MODULE: piloteUart
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
// #define PILOTEUART_PIN        GPIO_NUM_35



//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteUart_transmet(void);
void piloteUart_recoit(void);
void piloteUart_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif