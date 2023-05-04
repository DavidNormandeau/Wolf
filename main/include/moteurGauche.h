#ifndef MOTEURGAUCHE_H
#define MOTEURGAUCHE_H

//MODULE: detectionPiece
//DESCRIPTION: 
//HISTORIQUE:
// 2023-04-23, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "define.h")


//Dependances logicielles
//(copiez et adaptez ce qui suit dans "define.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
typedef enum {
    AVANCE,
    RECULE
} direction_t;

//Fonctions publiques:

void moteurGauche_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif