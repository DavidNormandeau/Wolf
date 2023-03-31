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
#include "driver/gpio.h"

//Dependances materielles:
#define PILOTEDETECTIONPIECE_S0_PIN             GPIO_NUM_36
#define PILOTEDETECTIONPIECE_S1_PIN             GPIO_NUM_39
#define PILOTEDETECTIONPIECE_S2_PIN             GPIO_NUM_34
#define PILOTEDETECTIONPIECE_S3_PIN             GPIO_NUM_35
#define PILOTEDETECTIONPIECE_EN1_2_PIN          GPIO_NUM_25
#define PILOTEDETECTIONPIECE_EN3_4_PIN          GPIO_NUM_33
#define PILOTEDETECTIONPIECE_EN5_6_PIN          GPIO_NUM_23
#define PILOTEDETECTIONPIECE_EN7_8_PIN          GPIO_NUM_22 
#define PILOTEDETECTIONPIECE_COM_PIN            GPIO_NUM_32
#define PILOTEMOTEUR1_DIR_PIN                   GPIO_NUM_26
#define PILOTEMOTEUR1_STEP_PIN                  GPIO_NUM_27
#define PILOTEMOTEUR2_DIR_PIN                   GPIO_NUM_2
#define PILOTEMOTEUR2_STEP_PIN                  GPIO_NUM_4
#define PILOTECLKBTNB_PIN                       GPIO_NUM_15
#define PILOTECLKBTNW_PIN                       GPIO_NUM_19
#define PILOTELIMITSWITCHX_PIN                  GPIO_NUM_18
#define PILOTELIMITSWITCHy_PIN                  GPIO_NUM_5
#define PILOTEELECTROAIMANT_PIN                 GPIO_NUM_21

#define A1  0
#define A2  8
#define A3  0
#define A4  8
#define A5  0
#define A6  8
#define A7  0
#define A8  8
#define B1  1
#define B2  9
#define B3  1
#define B4  9
#define B5  1
#define B6  9
#define B7  1
#define B8  9
#define C1  2
#define C2  10
#define C3  2
#define C4  10
#define C5  2
#define C6  10
#define C7  2
#define C8  10
#define D1  3
#define D2  11
#define D3  3
#define D4  11
#define D5  3
#define D6  11
#define D7  3
#define D8  11
#define E1  4
#define E2  12
#define E3  4
#define E4  12
#define E5  4
#define E6  12
#define E7  4
#define E8  12
#define F1  5
#define F2  13
#define F3  5
#define F4  13
#define F5  5
#define F6  13
#define F7  5
#define F8  13
#define G1  6
#define G2  14
#define G3  6
#define G4  14
#define G5  6
#define G6  14
#define G7  6
#define G8  14
#define H1  7
#define H2  15
#define H3  7
#define H4  15
#define H5  7
#define H6  15
#define H7  7
#define H8  15

#define DETECTIONPIECE_VALEUR_SI_PIECE_DETECTE  0
#define DETECTIONPIECE_VALEUR_SI_VIDE           1    
// #define INTERFACEB1_VALEUR_LUE_SI_APPUYE  0   
// #define INTERFACEB1_VALEUR_LUE_SI_RELACHE 1
// #define INTERFACEB1_DELAI_ANTI_REBOND_EN_MS  15
// #define INTERFACET1_VALEUR_POUR_ALLUMER  0   
// #define INTERFACET1_VALEUR_POUR_ETEINDRE 1

//Dependances logicielles:
// #define FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ 2000.0
// #define PILOTETIMER1MODE2_TAUX_DE_BITS 19200.0 //9600.0
// #define PILOTETIMER1MODE2_UTILISE_LE_DOUBLEUR_DE_TAUX  1
// #define INTERFACEB1_FREQUENCE_DES_LECTURES_EN_HZ  100.0
// #define INTERFACEB1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10
// #define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS  500.0
// #define PROCESSUSCLIGNOTANT_PERIODE_EN_MS 1000.0
// #define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_TRANSMISSIONS_EN_HZ 500.0
// #define SERVICEPROTOCOLE637_NOMBRE_DE_DONNEES_MAXIMUM  16
// #define SERVICEPROTOCOLE637_DEBUT_DE_TRAME  '$'
// #define SERVICEPROTOCOLE637_INSERTION 0x00
// #define SERVICEPROTOCOLE637_TEMPS_D_ATTENTE_MAXIMAL_EN_MS 4
// #define SERVICEPROTOCOLE637_FREQUENCE_MAXIMALE_DES_LECTURES_EN_HZ 2000.0

// #define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES  7
// #define INTERFACEB1_PHASE 0
// #define SERVICEPROTOCOLE637_PHASE_RECEPTION 1
// #define INTERFACES0009_PHASE_RECEPTION 2
// #define INTERFACES0009_PHASE_TRANSMISSION 5
// #define SERVICEPROTOCOLE637_PHASE_TRANSMISSION 3
// #define PROCESSUSBOUTONCONNECTE_PHASE 4
// #define PROCESSUSCLIGNOTANT_PHASE 6

// #define SERVICEPROTOCOLE637_DEBUG //activation de messages de debug

//INFORMATION PUBLIQUE:
//Definitions publiques:
// #define INFORMATION_DISPONIBLE  1
// #define INFORMATION_TRAITEE  0
// #define REQUETE_ACTIVE  1
// #define REQUETE_TRAITEE 0
// #define MODULE_EN_FONCTION 1
// #define MODULE_PAS_EN_FONCTION 0

//Fonctions publiques:
//pas de fonctions publiques

//Variables publiques:
//pas de variables publiques
#endif

