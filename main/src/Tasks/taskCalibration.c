//taskCalibration:
//Historique: 
// 2023-05-02, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "piloteLimitSwitchX.h"
#include "piloteLimitSwitchY.h"
#include "coreXY.h"
#include "taskCalibration.h"

//Definitions privees
//static const char* TAG = "TASK CALIBRATION";
#define CALIBRATION_NBRE_DE_STEP_ENTRE_LECTURE_LIMIT_SWITCH 4
#define CALIBRATION_VITESSE_LENTE                           3   //en ms
#define CALIBRATION_VITESSE_RAPIDE                          1   //en ms
#define CALIBRATION_NBRE_DE_STEP_VERS_POSITION_INITIAL_X    100
#define CALIBRATION_NBRE_DE_STEP_VERS_POSITION_INITIAL_Y    100

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
TaskHandle_t xHandleTaskCalibration = NULL;


//Definitions de fonctions publiques:
void taskCalibration(void * pvParameters)
{
    while(1)
    {
        xSemaphoreTake(semaphoreCalibration, portMAX_DELAY);

        //Déplacement lent vers limit switch X
        while(piloteLimitSwitchX_litLEntree() == 1) //à modifier
        {
            coreXY_deplaceEnNombreDeSteps(  CALIBRATION_NBRE_DE_STEP_ENTRE_LECTURE_LIMIT_SWITCH, 
                                            A_TO_H, 
                                            CALIBRATION_VITESSE_LENTE);
        }

        //Déplacement lent vers limit switch Y
        while(piloteLimitSwitchY_litLEntree() == 1) //à modifier
        {
            coreXY_deplaceEnNombreDeSteps(  CALIBRATION_NBRE_DE_STEP_ENTRE_LECTURE_LIMIT_SWITCH, 
                                            _8_TO_1, 
                                            CALIBRATION_VITESSE_LENTE);
        }

        //Déplacement rapide vers position départ
        coreXY_deplaceEnNombreDeSteps(  CALIBRATION_NBRE_DE_STEP_VERS_POSITION_INITIAL_X, 
                                        H_TO_A, 
                                        CALIBRATION_VITESSE_RAPIDE);

        coreXY_deplaceEnNombreDeSteps(  CALIBRATION_NBRE_DE_STEP_ENTRE_LECTURE_LIMIT_SWITCH, 
                                        _1_TO_8, 
                                        CALIBRATION_VITESSE_RAPIDE);

        //dire que la calibration est terminée
        //à compléter
    }
    xSemaphoreGive(semaphoreCalibration);

    vTaskDelete(xHandleTaskCalibration);
}





void taskCalibration_initialise(void)
{
    xTaskCreatePinnedToCore(taskCalibration, 
                            "TaskCalibration", 
                            TASKCALIBRATION_STACK_SIZE, 
                            NULL, 
                            TASKCALIBRATION_PRIORITY, 
                            &xHandleTaskCalibration, 
                            TASKCALIBRATION_CORE
    );


}