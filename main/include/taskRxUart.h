#ifndef TASKRXUART_H
#define TASKRXUART_H

//MODULE: taskRxUart
//DESCRIPTION: 
//HISTORIQUE:
// 2023-05-08, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "define.h")





//Dependances logicielles
//(copiez et adaptez ce qui suit dans "define.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
#define TASKRXUART_PAS_D_ERREURS 0
#define TASKRXUART_ERREUR_EN_ATTENTE 1
#define TASKRXUART_ERREUR_TEMPS_DEPASSE 2
#define TASKRXUART_ERREUR_LONGUEUR_NULLE 3
#define TASKRXUART_ERREUR_LONGUEUR_TROP_GRANDE 4
#define TASKRXUART_ERREUR_INSERTION_NON_NULLE 5
#define TASKRXUART_ERREUR_MAUVAIS_CHECKSUM 6

typedef struct
{
  char octetsRecus[TASKRXUART_NOMBRE_DE_DONNEES_MAXIMUM];
  unsigned char nombreARecevoir;
  unsigned char statut;
} TASKRXUART;

//Fonctions publiques:
void taskRxUart();
void taskRxUart_initialise(void);

//Variables publiques:
extern QueueHandle_t queueRxUart;
extern TaskHandle_t xHandleTaskRxUart;

#endif
