#ifndef TASKGESTIONCONTROLEUR1_H
#define TASKGESTIONCONTROLEUR1_H

//MODULE: taskGestionControleur1
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
void taskGestionControleur1(void *pvParameters);
void taskGestionControleur1_initialise(void);

//Variables publiques:
extern QueueHandle_t queueGestionControleur1;
extern TaskHandle_t xHandletaskGestionControleur1;

#endif
