#ifndef LIMITSWITCHX_H
#define LIMITSWITCHX_H

//MODULE: limitSwitchX
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
#define LIMITSWITCHX_ETAT_SI_BOUTON_APPUYE  0
#define LIMITSWITCHX_ETAT_SI_BOUTON_RELACHE 1

//Fonctions publiques:
unsigned char limitSwitchX_litLEtat(void);
void limitSwitchX_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif