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
//pas de definitions publiques

//Fonctions publiques:
void taskTxUart();
void taskTxUart_initialise(void);

//Variables publiques:
TaskHandle_t xHandleTaskTxUart;

#endif
