/*
 fonction.c

 Définition des fonctions de base de ROBUS
*/

#include <Arduino.h>
#include <LibRobus.h>

#include "fonctions.h"

// Circonférence des roues
#define CIRCONFERENCE 24.25 //23,94 selon le wiki de LibRobus
// Nombre de pulse des encodeur par tour de roue
#define PULSEPARTOUR 3200
// Valeur des moteurs
#define GAUCHE 0
#define DROIT 1

// Avancer en fonction d'une distance en cm et d'une vitesse
// Speed: positif = avance, négatif = recule
void cmMove(float cm, float speed)
{
    int nbrTour = (cm * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(GAUCHE);
    ENCODER_ReadReset(DROIT);


    while (ENCODER_Read(GAUCHE) != nbrTour && ENCODER_Read(DROIT) != nbrTour)
    {
        MOTOR_SetSpeed(GAUCHE, speed);
        MOTOR_SetSpeed(DROIT, speed);
    }

    MOTOR_SetSpeed(GAUCHE, 0);
    MOTOR_SetSpeed(DROIT, 0);    
}
