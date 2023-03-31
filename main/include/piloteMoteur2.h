#ifndef PILOTEMOTEUR2_H
#define PILOTEMOTEUR2_H

//MODULE: piloteMoteur2
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
// #define PILOTEMOTEUR1_PIN        GPIO_NUM_35



//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteMoteur2_metDirA(unsigned char valeur);
void piloteMoteur2_metStepA(unsigned char valeur);
void piloteMoteur2_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif