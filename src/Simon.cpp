#include "MyIncludes.h"
#define CIRCONFERENCE 23.94
#define PULSEPARTOUR 3200
#define UnHuit 7.5

void TurnNoMoving(float speed, float huitTour, bool direction)
{
    int pulseDistance = ((UnHuit * huitTour * PULSEPARTOUR) / CIRCONFERENCE) - 85;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int time = 0;
    int oldTime = 0;
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed [2] = {1,1};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit

    if(direction)//Turn Right
    {
        while ((ENCODER_Read(LEFT) < pulseDistance) && (ENCODER_Read(RIGHT) > (0 - pulseDistance)))
        {
            time = millis();   
            if(time - oldTime > 20)
            { 
                lastLeft = newLeft;
                lastRight = newRight;
                newLeft = ENCODER_Read(LEFT);
                newRight = ENCODER_Read(RIGHT);
                Serial.println("Left");
                Serial.println(newLeft - lastLeft);
                Serial.println("Right");
                Serial.println(0 - (newRight - lastRight));
                Serial.println(" ");
                AdjustSpeed(newLeft - lastLeft, 0,  0 - (newRight - lastRight), 0, pSpeed, speed);
                MOTOR_SetSpeed(LEFT, speed * pSpeed[0]); //- pSpeed[0]);
                MOTOR_SetSpeed(RIGHT, (0 - speed) * pSpeed[1]);
            }
        }
    }
    else
    {
        while ((ENCODER_Read(LEFT) > (0 - pulseDistance)) && (ENCODER_Read(RIGHT) < pulseDistance))
        {
            time = millis();   
            if(time - oldTime > 20)
            { 
                lastLeft = newLeft;
                lastRight = newRight;
                newLeft = ENCODER_Read(LEFT);
                newRight = ENCODER_Read(RIGHT); 
                Serial.println("Left");
                Serial.println(newLeft - lastLeft);
                Serial.println("Right");
                Serial.println(0 - (newRight - lastRight));
                Serial.println(" ");        
                AdjustSpeed(0 - (newLeft - lastLeft), 0 , newRight - lastRight, 0 , pSpeed,speed);
                MOTOR_SetSpeed(LEFT, (0 - speed) * pSpeed[0]); //- pSpeed[0]);
                MOTOR_SetSpeed(RIGHT, speed * pSpeed[1]);
            }
        }  
    }
    
     MOTOR_SetSpeed(RIGHT, 0);
     MOTOR_SetSpeed(LEFT, 0); 
}


void AdjustSpeed(int gauche,int gaucheDistance, int droit, int droitDistance, float* pSpeed, float speed)
{
    if(gauche > droit)//Grosse ajustement          Gauche trop rapide
    {   
        int erreur = gauche - droit;
        if(pSpeed[1] < 1)pSpeed[1] += (0.0001 * erreur);
        else pSpeed[0] -= (0.0001 * erreur);
        Serial.println("Erreur G > D");
        Serial.println(erreur);
    }
    else if(droit > gauche)//Grosse ajustement    Droit trop rapide
    {
        int erreur = droit - gauche;
        if(pSpeed[1] < 1)pSpeed[1] += (0.0001 * erreur);
        else pSpeed[1] -= (0.0001 * erreur);
        Serial.println("Erreur D > G");
        Serial.println(erreur);
    }
}
