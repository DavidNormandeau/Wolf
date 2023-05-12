#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: Wolf
//DESCRIPTION: 

//HISTORIQUE:
// 2023-03-30, David Normandeau: creation

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

//DEFINITIONS REQUISES PAR LE PROGRAMME:
#include "esp_log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "sdkconfig.h"



//Dependances materielles:
#define PILOTEDETECTIONPIECE_S0_PIN             GPIO_NUM_32
#define PILOTEDETECTIONPIECE_S1_PIN             GPIO_NUM_33
#define PILOTEDETECTIONPIECE_S2_PIN             GPIO_NUM_25
#define PILOTEDETECTIONPIECE_S3_PIN             GPIO_NUM_26
#define PILOTEDETECTIONPIECE_EN1_2_PIN          GPIO_NUM_23
#define PILOTEDETECTIONPIECE_EN3_4_PIN          GPIO_NUM_22
#define PILOTEDETECTIONPIECE_EN5_6_PIN          GPIO_NUM_4
#define PILOTEDETECTIONPIECE_EN7_8_PIN          GPIO_NUM_27 
#define PILOTEDETECTIONPIECE_COM_PIN            GPIO_NUM_36
#define PILOTEMOTEURGAUCHE_DIR_PIN              GPIO_NUM_5
#define PILOTEMOTEURGAUCHE_STEP_PIN             GPIO_NUM_18
#define PILOTEMOTEURDROIT_DIR_PIN               GPIO_NUM_19
#define PILOTEMOTEURDROIT_STEP_PIN              GPIO_NUM_21
#define PILOTELIMITSWITCHX_PIN                  GPIO_NUM_34
#define PILOTELIMITSWITCHY_PIN                  GPIO_NUM_35
#define PILOTEELECTROAIMANT_PIN                 GPIO_NUM_2
#define PILOTEUART2_TX_PIN                      GPIO_NUM_17
#define PILOTEUART2_RX_PIN                      GPIO_NUM_16
// #define PILOTECLKBTNB_PIN                       GPIO_NUM_12
// #define PILOTECLKBTNW_PIN                       GPIO_NUM_39

// #define A1  0
// #define A2  8
// #define A3  0
// #define A4  8
// #define A5  0
// #define A6  8
// #define A7  0
// #define A8  8
// #define B1  1
// #define B2  9
// #define B3  1
// #define B4  9
// #define B5  1
// #define B6  9
// #define B7  1
// #define B8  9
// #define C1  2
// #define C2  10
// #define C3  2
// #define C4  10
// #define C5  2
// #define C6  10
// #define C7  2
// #define C8  10
// #define D1  3
// #define D2  11
// #define D3  3
// #define D4  11
// #define D5  3
// #define D6  11
// #define D7  3
// #define D8  11
// #define E1  4
// #define E2  12
// #define E3  4
// #define E4  12
// #define E5  4
// #define E6  12
// #define E7  4
// #define E8  12
// #define F1  5
// #define F2  13
// #define F3  5
// #define F4  13
// #define F5  5
// #define F6  13
// #define F7  5
// #define F8  13
// #define G1  6
// #define G2  14
// #define G3  6
// #define G4  14
// #define G5  6
// #define G6  14
// #define G7  6
// #define G8  14
// #define H1  7
// #define H2  15
// #define H3  7
// #define H4  15
// #define H5  7
// #define H6  15
// #define H7  7
// #define H8  15

#define DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE      0
#define DETECTIONPIECE_VALEUR_SI_VIDE               1
#define ELECTROAIMANT_VALEUR_POUR_ACTIVER_AIMANT    1
#define ELECTROAIMANT_VALEUR_POUR_ETEINDRE_AIMANT   0    
// #define INTERFACEB1_VALEUR_LUE_SI_APPUYE  0   
// #define INTERFACEB1_VALEUR_LUE_SI_RELACHE 1
// #define INTERFACEB1_DELAI_ANTI_REBOND_EN_MS  15
// #define INTERFACET1_VALEUR_POUR_ALLUMER  0   
// #define INTERFACET1_VALEUR_POUR_ETEINDRE 1

//Dependances logicielles:
#define PILOTEUART_BAUD_RATE 115200
// #define FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ 2000.0
// #define PILOTETIMER1MODE2_TAUX_DE_BITS 19200.0 //9600.0
// #define PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX  1
// #define INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ  100.0
// #define INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10
// #define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS  500.0
// #define PROCESSUSCLIGNOTANT_PERIODE_EN_MS 1000.0
// #define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ 500.0
#define TASKTXUART_NOMBRE_DE_DONNEES_MAXIMUM    16
#define TASKRXUART_NOMBRE_DE_DONNEES_MAXIMUM    TASKTXUART_NOMBRE_DE_DONNEES_MAXIMUM
#define TASKRXUART_DEBUT_DE_TRAME               '$'
#define TASKTXUART_DEBUT_DE_TRAME               TASKRXUART_DEBUT_DE_TRAME 
#define TASKTXUART_INSERTION                    0x00
#define TASKRXUART_INSERTION                    TASKTXUART_INSERTION
// #define SERVICEPROTOCOLE637_TEMPS_D_ATTENTE_MAXIMAL_EN_MS 4
// #define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ 2000.0
#define NBRE_DE_STEP_DANS_UNE_CASE  50 //??????????????????????
#define COEFFICIENT_DIAGONALE       1.44  //??????????????????????

#define CHARIOT_POSITION_INITIALE_X    5     //E7
#define CHARIOT_POSITION_INITIALE_Y    7

#define TASKCALIBRATION_DEPLACEMENT_X  100      //??????????????à déterminer??????????????en nombre de steps    
#define TASKCALIBRATION_DEPLACEMENT_y  100

//Tasks
#define TASKTXUART_STACK_SIZE             (2*1024)
#define TASKTXUART_PRIORITY               0
#define TASKTXUART_CORE                   0

#define TASKRXUART_STACK_SIZE             (2*1024)
#define TASKRXUART_PRIORITY               0
#define TASKRXUART_CORE                   0  

#define TASKDEPLACEMENTPIECE_STACK_SIZE   (2*1024)
#define TASKDEPLACEMENTPIECE_PRIORITY     2
#define TASKDEPLACEMENTPIECE_CORE         0

#define TASKGESTIONCONTROLEUR1_STACK_SIZE (2*1024)
#define TASKGESTIONCONTROLEUR1_PRIORITY   2
#define TASKGESTIONCONTROLEUR1_CORE       0 

#define TASKCALIBRATION_STACK_SIZE        (2*1024)
#define TASKCALIBRATION_PRIORITY          2
#define TASKCALIBRATION_CORE              0


typedef enum
{
   A1 = 0, B1, C1, D1, E1, F1, G1, H1,
   A2, B2, C2, D2, E2, F2, G2, H2,
   A3, B3, C3, D3, E3, F3, G3, H3,
   A4, B4, C4, D4, E4, F4, G4, H4,
   A5, B5, C5, D5, E5, F5, G5, H5,
   A6, B6, C6, D6, E6, F6, G6, H6,
   A7, B7, C7, D7, E7, F7, G7, H7,
   A8, B8, C8, D8, E8, F8, G8, H8 
} case_t;

typedef struct
{
   unsigned char r0  : 1;
   unsigned char r1  : 1;
   unsigned char r2  : 1;
   unsigned char r3  : 1;
   unsigned char r4  : 1;
   unsigned char r5  : 1;
   unsigned char r6  : 1;
   unsigned char r7  : 1;

} rank_bit_t;

enum file { FILE_A = 0, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};

typedef enum
{
   CAPTURE_A_FAIRE = 0,
   NORMAL,
   EN_PASSANT,
   ROQUE_COURT_BLAMC,
   ROQUE_LONG_BLANC,
   ROQUE_COURT_NOIR,
   ROQUE_LONG_NOIR
} type_deplacement_piece_t;

//INFORMATION PUBLIQUE:
//Definitions publiques:
// #define INFORMATION_DISPONIBLE  1
// #define INFORMATION_TRAITEE  0
#define REQUETE_ACTIVE  1
#define REQUETE_TRAITEE 0
// #define MODULE_EN_FONCTION 1
// #define MODULE_PAS_EN_FONCTION 0

//Fonctions publiques:
//pas de fonctions publiques

//Variables publiques:
//pas de variable publiques
#endif

