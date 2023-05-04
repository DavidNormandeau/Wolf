#ifndef PILOTEMOTEURDROIT_H
#define PILOTEMOTEURDROIT_H

//MODULE: piloteMoteurDroit
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "define.h")
// #define PILOTEMOTEURDROIT_PIN        GPIO_NUM_35



//Dependances logicielles
//(copiez et adaptez ce qui suit dans "define.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteMoteurDroit_metDirA(unsigned char valeur);
void piloteMoteurDroit_metStepA(unsigned char valeur);
void piloteMoteurDroit_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif