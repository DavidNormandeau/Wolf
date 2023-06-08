#ifndef TASKCALIBRATION_H
#define TASKCALIBRATION_H

//MODULE: taskCalibration 
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
#define TASKCALIBRATION_PAS_D_ERREUR    0
#define TASKCALIBRATION_ERREUR          1

// typedef struct
// {
//     unsigned char requete;
//     unsigned char statut;
// } TASKCALIBRATION;


//Fonctions publiques:
void taskCalibration(void *pvParameters);
void taskCalibration_initialise(void);

//Variables publiques:
extern TaskHandle_t xHandleTaskCalibration;
//extern TASKCALIBRATION calibration;
extern SemaphoreHandle_t semaphoreDebutCalibration;
extern SemaphoreHandle_t semaphoreFinCalibration;

#endif
