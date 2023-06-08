#ifndef PILOTEELECTROAIMANT_H
#define PILOTEELECTROAIMANT_H

//MODULE: piloteElectroaimant
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "define.h")
// #define PILOTEELECTROAIMANT_PIN        GPIO_NUM_35



//Dependances logicielles
//(copiez et adaptez ce qui suit dans "define.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteElectroaimant_metLaSortieA(unsigned char valeur);
void piloteElectroaimant_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif