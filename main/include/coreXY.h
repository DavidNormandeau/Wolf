#ifndef COREXY_H
#define COREXY_H

//MODULE: coreXY
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
// #define COREXY_PIN        GPIO_NUM_35



//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
typedef enum {
    A_TO_H,
    H_TO_A,
    _1_TO_8,
    _8_TO_1,
    A1_TO_H8,
    H8_TO_A1,
    H1_TO_A8,
    A8_TO_H1    
} direction_t;

//Fonctions publiques:
void coreXY_deplaceEnNombreDeSteps(int nbreDeSteps, direction_t direction, int vitesse);
void coreXY_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif