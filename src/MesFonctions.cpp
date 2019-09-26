
#include"MyIncludes.h"

void CmMove(float cm, float speed)
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