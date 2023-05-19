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
#define PILOTELIMITSWITCHX_PIN                  GPIO_NUM_35
#define PILOTELIMITSWITCHY_PIN                  GPIO_NUM_34
#define PILOTEELECTROAIMANT_PIN                 GPIO_NUM_2
#define PILOTEUART2_TX_PIN                      GPIO_NUM_17
#define PILOTEUART2_RX_PIN                      GPIO_NUM_16
// #define PILOTECLKBTNB_PIN                       GPIO_NUM_12
// #define PILOTECLKBTNW_PIN                       GPIO_NUM_39

#define DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE      0
#define DETECTIONPIECE_VALEUR_SI_CASE_VIDE          1
#define ELECTROAIMANT_VALEUR_POUR_ACTIVER_AIMANT    1
#define ELECTROAIMANT_VALEUR_POUR_ETEINDRE_AIMANT   0    
// #define INTERFACEB1_VALEUR_LUE_SI_APPUYE  0   
// #define INTERFACEB1_VALEUR_LUE_SI_RELACHE 1
// #define INTERFACEB1_DELAI_ANTI_REBOND_EN_MS  15
// #define INTERFACET1_VALEUR_POUR_ALLUMER  0   
// #define INTERFACET1_VALEUR_POUR_ETEINDRE 1

//Dependances logicielles:
#define PILOTEUART_BAUD_RATE 115200
// #define INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ  100.0
// #define INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10
// #define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ 500.0
#define TASKTXUART_NOMBRE_DE_DONNEES_MAXIMUM    16
#define TASKRXUART_NOMBRE_DE_DONNEES_MAXIMUM    TASKTXUART_NOMBRE_DE_DONNEES_MAXIMUM
#define TASKRXUART_DEBUT_DE_TRAME               '$'
#define TASKTXUART_DEBUT_DE_TRAME               TASKRXUART_DEBUT_DE_TRAME 
#define TASKTXUART_INSERTION                    0x00
#define TASKRXUART_INSERTION                    TASKTXUART_INSERTION
// #define SERVICEPROTOCOLE637_TEMPS_D_ATTENTE_MAXIMAL_EN_MS 4
// #define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ 2000.0
#define NBRE_DE_STEP_DANS_UNE_CASE  (2*NBRE_DE_STEP_DANS_UNE_DEMI_CASE) 
#define NBRE_DE_STEP_DANS_UNE_DEMI_CASE  94
#define COEFFICIENT_DIAGONALE       1.97  //Meilleur: entre 1.95 et 2

#define CHARIOT_POSITION_INITIALE_FILE    9     //E7
#define CHARIOT_POSITION_INITIALE_RANK    13

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
   H1 = 0, G1, F1, E1, D1, C1, B1, A1,
   H2, G2, F2, E2, D2, C2, B2, A2,
   H3, G3, F3, E3, D3, C3, B3, A3,
   H4, G4, F4, E4, D4, C4, B4, A4,
   H5, G5, F5, E5, D5, C5, B5, A5,
   H6, G6, F6, E6, D6, C6, B6, A6,
   H7, G7, F7, E7, D7, C7, B7, A7,
   H8, G8, F8, E8, D8, C8, B8, A8 
} case_t;

typedef struct
{
   char A   : 1;
   char B   : 1;
   char C   : 1;
   char D   : 1;
   char E   : 1;
   char F   : 1;
   char G   : 1;
   char H   : 1;

} rank_bit_t;

typedef union 
{
   uint64_t entier64; 
   char cTab[8];
   rank_bit_t rank_bit[8];
} position_piece_t;


enum file { FILE_A = 0, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};
enum rank {RANK_1 = 0, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8};

typedef enum
{
   CAPTURE_A_FAIRE = 0,
   NORMAL,
   EN_PASSANT,
   ROQUE_COURT_BLANC,
   ROQUE_LONG_BLANC,
   ROQUE_COURT_NOIR,
   ROQUE_LONG_NOIR
} type_deplacement_piece_t;

//INFORMATION PUBLIQUE:
//Definitions publiques:
// #define INFORMATION_DISPONIBLE  1
// #define INFORMATION_TRAITEE  0
#define REQUETE_ACTIVE        1
#define REQUETE_TRAITEE       0
#define BOUTON_A_ETE_APPUYE   1
#define BOUTON_PAS_ETE_APPUYE 0

// #define MODULE_EN_FONCTION 1
// #define MODULE_PAS_EN_FONCTION 0

//Fonctions publiques:
//pas de fonctions publiques

//Variables publiques:
// extern unsigned char tabPieceDetecteeSurEchiquier[64];
// extern unsigned char tabPieceDetecteeSurEchiquierPrecedent[64];
extern unsigned char tabPieceDetecteeSurEchiquier[8][8];
extern unsigned char tabPieceDetecteeSurEchiquierPrecedent[8][8];
extern position_piece_t pieceDetecteeSurEchiquier;
extern position_piece_t pieceDetecteeSurEchiquierPrecedent;
#endif

