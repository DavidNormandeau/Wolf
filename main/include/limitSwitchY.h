#ifndef LIMITSWITCHY_H
#define LIMITSWITCHY_H

//MODULE: limitSwitchY
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "define.h")
// pas de dépendances matérielles



//Dependances logicielles
//(copiez et adaptez ce qui suit dans "define.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define LIMITSWITCHY_ETAT_SI_BOUTON_APPUYE  0
#define LIMITSWITCHY_ETAT_SI_BOUTON_RELACHE 1

//Fonctions publiques:
unsigned char limitSwitchY_litLEtat(void);
void limitSwitchY_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif