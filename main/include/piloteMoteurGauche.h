#ifndef PILOTEMOTEURGAUCHE_H
#define PILOTEMOTEURGAUCHE_H

//MODULE: piloteMoteurGauche
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
// #define PILOTEMOTEURGAUCHE_PIN        GPIO_NUM_35



//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteMoteurGauche_metDirA(unsigned char valeur);
void piloteMoteurGauche_metStepA(unsigned char valeur);
void piloteMoteurGauche_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif