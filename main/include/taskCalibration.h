#ifndef TASKCALIBRATION_H
#define TASKCALIBRATION_H

//MODULE: taskCalibration
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
void taskCalibration(void *pvParameters);
void taskCalibration_initialise(void);

//Variables publiques:
extern TaskHandle_t xHandleTaskCalibration;

#endif
