#ifndef PILOTEDETECTIONPIECE_H
#define PILOTEDETECTIONPIECE_H

//MODULE: detectionPiece
//DESCRIPTION: 
//HISTORIQUE:
// 2023-03-30, David Normandeau, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
// #define PILOTEPIECEDETECTION_S0_PIN        GPIO_NUM_35
// #define PILOTEPIECEDETECTION_S1_PIN        GPIO_NUM_35
// #define PILOTEPIECEDETECTION_S2_PIN        GPIO_NUM_35
// #define PILOTEPIECEDETECTION_S3_PIN        GPIO_NUM_35
// #define PILOTEPIECEDETECTION_EN1_2_PIN     GPIO_NUM_35
// #define PILOTEPIECEDETECTION_EN3_4_PIN     GPIO_NUM_35
// #define PILOTEPIECEDETECTION_EN5_6_PIN     GPIO_NUM_35
// #define PILOTEPIECEDETECTION_EN7_8_PIN     GPIO_NUM_35
// #define PILOTEPIECEDETECTION_COM_PIN       GPIO_NUM_35


//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
// pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void piloteDetectionPiece_metS0A(unsigned char valeur);
void piloteDetectionPiece_metS1A(unsigned char valeur);
void piloteDetectionPiece_metS2A(unsigned char valeur);
void piloteDetectionPiece_metS3A(unsigned char valeur);
void piloteDetectionPiece_metEN1_2A(unsigned char valeur);
void piloteDetectionPiece_metEN3_4A(unsigned char valeur);
void piloteDetectionPiece_metEN5_6A(unsigned char valeur);
void piloteDetectionPiece_metEN7_8A(unsigned char valeur);
unsigned char piloteDetectionPiece_litCOM(void);
void piloteDetectionPiece_initialise(void);

//Variables publiques:
// pas de variables publiques

#endif