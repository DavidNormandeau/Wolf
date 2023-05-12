#ifndef TASKTXUART_H
#define TASKTXUART_H

//MODULE: taskTxUart
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
    char octetsATransmettre[TASKRXUART_NOMBRE_DE_DONNEES_MAXIMUM];
    unsigned char nombreOctetsATransmettre;
} TASKTXUART;


//Fonctions publiques:
void taskTxUart();
void taskTxUart_initialise(void);

//Variables publiques:
extern QueueHandle_t queueTxUart;
extern TaskHandle_t xHandleTaskTxUart;

#endif
