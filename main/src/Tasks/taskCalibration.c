//taskCalibration:
//Historique: 
// 2023-05-02, David Normandeau, creation

//INCLUSIONS
#include "define.h"
#include "limitSwitchX.h"
#include "limitSwitchY.h"
#include "coreXY.h"
#include "taskCalibration.h"

//Definitions privees
static const char* TAG = "TASK CALIBRATION";
#define CALIBRATION_NBRE_DE_STEP_ENTRE_LECTURE_LIMIT_SWITCH 4
#define CALIBRATION_VITESSE_LENTE                           3   //en ms
#define CALIBRATION_VITESSE_RAPIDE                          1   //en ms


//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
TaskHandle_t xHandleTaskCalibration = NULL;
SemaphoreHandle_t semaphoreDebutCalibration;
SemaphoreHandle_t semaphoreFinCalibration;


//Definitions de fonctions publiques:
void taskCalibration(void * pvParameters)
{

    while(1)
    {
        xSemaphoreTake(semaphoreDebutCalibration, portMAX_DELAY);

        //Déplacement lent vers limit switch X
        while(limitSwitchX_litLEtat() == LIMITSWITCHX_ETAT_SI_BOUTON_RELACHE) 
        {
            coreXY_deplaceEnNombreDeSteps(  CALIBRATION_NBRE_DE_STEP_ENTRE_LECTURE_LIMIT_SWITCH, 
                                            A_TO_H, 
                                            CALIBRATION_VITESSE_LENTE);
        }

        //Déplacement lent vers limit switch Y
        while(limitSwitchY_litLEtat() == LIMITSWITCHY_ETAT_SI_BOUTON_RELACHE) 
        {
            coreXY_deplaceEnNombreDeSteps(  CALIBRATION_NBRE_DE_STEP_ENTRE_LECTURE_LIMIT_SWITCH, 
                                            _8_TO_1, 
                                            CALIBRATION_VITESSE_LENTE);
        }

        //Déplacement rapide vers position départ
        coreXY_deplaceEnNombreDeSteps(  CALIBRATION_NBRE_DE_STEP_VERS_POSITION_INITIAL_FILE, 
                                        H_TO_A, 
                                        CALIBRATION_VITESSE_RAPIDE);

        coreXY_deplaceEnNombreDeSteps(  CALIBRATION_NBRE_DE_STEP_VERS_POSITION_INITIAL_RANK, 
                                        _1_TO_8, 
                                        CALIBRATION_VITESSE_RAPIDE);

        positionChariot.file = CHARIOT_POSITION_INITIALE_FILE;
        positionChariot.rank = CHARIOT_POSITION_INITIALE_RANK;

        //dire que la calibration est terminée
        xSemaphoreGive(semaphoreFinCalibration);
        ESP_LOGI(TAG, "Calibration terminée");
    }
   

    vTaskDelete(xHandleTaskCalibration);
}





void taskCalibration_initialise(void)
{
    semaphoreDebutCalibration = xSemaphoreCreateBinary();
    semaphoreFinCalibration = xSemaphoreCreateBinary();

    xTaskCreatePinnedToCore(taskCalibration, 
                            "TaskCalibration", 
                            TASKCALIBRATION_STACK_SIZE, 
                            NULL, 
                            TASKCALIBRATION_PRIORITY, 
                            &xHandleTaskCalibration, 
                            TASKCALIBRATION_CORE
    );
}