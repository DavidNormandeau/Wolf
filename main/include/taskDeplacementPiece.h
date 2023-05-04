#ifndef TASKDEPLACEMENTPIECE_H
#define TASKDEPLACEMENTPIECE_H

//MODULE: taskTxUart
//DESCRIPTION: 
//HISTORIQUE:
// 2023-04-25, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")


//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
typedef struct 
{
    float x;
    float y;
} coordonneeEchiquier_t;

typedef struct 
{
    type_deplacement_piece_t type;
    coordonneeEchiquier_t positionDepart;
    coordonneeEchiquier_t positionArrivee;
} info_deplacement_t;


//Fonctions publiques:
void taskDeplacementPiece();
void taskDeplacementPiece_initialise(void);

//Variables publiques:
TaskHandle_t xHandleTaskDeplacementPiece;

#endif
