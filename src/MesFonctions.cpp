
#include"MyIncludes.h"

void CmMove(float cm, float speed)
{
    int nbrTour = (cm * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed [2] = {0,0};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit

    while (ENCODER_Read(LEFT) < nbrTour && ENCODER_Read(RIGHT) < nbrTour)
    {
        //lastLeft = newLeft;
        //lastRight = newRight;
        //newLeft = ENCODER_Read(LEFT);
        //newRight = ENCODER_Read(RIGHT);
        //AdjustSpeed(newLeft - lastLeft,newRight - lastRight,pSpeed);
        AdjustSpeed(ENCODER_Read(LEFT),ENCODER_Read(RIGHT),pSpeed);
        MOTOR_SetSpeed(LEFT, speed - pSpeed[0]);
        MOTOR_SetSpeed(RIGHT, speed - pSpeed[1]);
        delayMicroseconds(1);
    }

    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);    
}

/*
Il faut faire une fonction qui sort 2 pourcentage de réduction des pourcentage de vitesse
% of %
 */
void AdjustSpeed(int gauche, int droit, float* pSpeed)
{
    if(gauche > droit + 20)//Grosse ajustement          Gauche trop rapide
    {   
        if(pSpeed[1] > 0.00005)pSpeed[1]-=0.00005;
        else pSpeed[0] += 0.00005;
    }
    else if(droit > gauche  + 20)//Grosse ajustement    Droit trop rapide
    {
        if(pSpeed[0] > 0.00005)pSpeed[0]-=0.00005;
        else pSpeed[1] += 0.00005;
    }
    else if(gauche > droit)
    {
        if(pSpeed[1] > 0.00001)pSpeed[1]-=0.00001;
        else pSpeed[0] += 0.00001;
    }
    else if(gauche < droit)
    {
        if(pSpeed[0] > 0.00001)pSpeed[0]-=0.00001;
        else pSpeed[1] += 0.00001;
    }
}

