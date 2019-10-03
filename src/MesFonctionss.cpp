
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
    float pSpeed [2] = {1,1};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit

    while ((ENCODER_Read(LEFT) < nbrTour) && (ENCODER_Read(RIGHT) < nbrTour))
    {
        delay(20);
        lastLeft = newLeft;
        lastRight = newRight;
        newLeft = ENCODER_Read(LEFT);
        newRight = ENCODER_Read(RIGHT);
        AdjustSpeed(newLeft - lastLeft,newRight - lastRight,pSpeed);
        MOTOR_SetSpeed(LEFT, speed * pSpeed[0]); //- pSpeed[0]);
        MOTOR_SetSpeed(RIGHT, speed * pSpeed[1]);
    }
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);    
}

/*
speed : speed entre 0 et 1 où 1 est 100%
huitTour : 1 = 1 huitieme de tour// 8 = 1 TOUR
direction : 0 = Gauche // 1 = Droit
*/
void TurnNoMoving(float speed, float huitTour, bool direction)
{
    int nbrTour = (UnHuit * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed [2] = {1,1};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit
    if(direction)//Turn Right
    {
        while ((ENCODER_Read(LEFT) < nbrTour) && (ENCODER_Read(RIGHT) > (0 - nbrTour)))
        {
            delay(20);
            lastLeft = newLeft;
            lastRight = newRight;
            newLeft = ENCODER_Read(LEFT);
            newRight = ENCODER_Read(RIGHT);
            Serial.println("Left");
            Serial.println(newLeft - lastLeft);
            Serial.println("Right");
            Serial.println(0 - (newRight - lastRight));
            Serial.println(" ");
            AdjustSpeed(newLeft - lastLeft, 0 - (newRight - lastRight),pSpeed);
            MOTOR_SetSpeed(LEFT, speed * pSpeed[0]); //- pSpeed[0]);
            MOTOR_SetSpeed(RIGHT, (0 - speed) * pSpeed[1]);
        }
    }
    else
    {
        while ((ENCODER_Read(LEFT) > (0 - nbrTour)) && (ENCODER_Read(RIGHT) < nbrTour))
        {
            delay(20);
            lastLeft = newLeft;
            lastRight = newRight;
            newLeft = ENCODER_Read(LEFT);
            newRight = ENCODER_Read(RIGHT);          
            AdjustSpeed(0 - (newLeft - lastLeft),newRight - lastRight,pSpeed);
            MOTOR_SetSpeed(LEFT, (0 - speed) * pSpeed[0]); //- pSpeed[0]);
            MOTOR_SetSpeed(RIGHT, speed * pSpeed[1]);
        }  
    }
    
     MOTOR_SetSpeed(RIGHT, 0);
     MOTOR_SetSpeed(LEFT, 0); 
}

void AdjustSpeed(int gauche, int droit, float* pSpeed)
{
    if(gauche > droit)//Grosse ajustement          Gauche trop rapide
    {   
        int erreur = gauche - droit;
        if(pSpeed[1] < 1)pSpeed[1] += (0.0001 * erreur);
        else pSpeed[0] -= (0.0001 * erreur);
    }
    else if(droit > gauche)//Grosse ajustement    Droit trop rapide
    {
        int erreur = droit - gauche;
        if(pSpeed[1] < 1)pSpeed[1] += (0.0001 * erreur);
        else pSpeed[1] -= (0.0001 * erreur);
    }

}