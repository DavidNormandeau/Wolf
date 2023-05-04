#ifndef DETECTIONPIECE_H
#define DETECTIONPIECE_H

//MODULE: detectionPiece
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "define.h")


//Dependances logicielles
//(copiez et adaptez ce qui suit dans "define.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
unsigned char detectionPiece_litLaCase(case_t caseALire);
void detectionPiece_litLEchiquier(unsigned char* echiquier);
void detectionPiece_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif