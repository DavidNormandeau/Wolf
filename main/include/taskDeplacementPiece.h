#ifndef TASKDEPLACEMENTPIECE_H
#define TASKDEPLACEMENTPIECE_H

//MODULE: taskDeplacementPiece
//DESCRIPTION: 
//HISTORIQUE:
// 2023-04-25, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "define.h")


//Dependances logicielles
//(copiez et adaptez ce qui suit dans "define.h")
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

typedef struct
{
    unsigned char statut;
    unsigned char requete;
} DEPLACEMENTPIECE;

#define DEPLACEMENTPIECE_PAS_D_ERREUR   0
#define DEPLACEMENTPIECE_ERREUR         1

//Fonctions publiques:
void taskDeplacementPiece(void *pvParameters);
void taskDeplacementPiece_initialise(void);

//Variables publiques:
extern QueueHandle_t queueDeplacementPiece;
extern TaskHandle_t xHandleTaskDeplacementPiece;
extern DEPLACEMENTPIECE deplacementPiece;

#endif
