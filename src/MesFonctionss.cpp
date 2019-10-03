
#include"MyIncludes.h"

void CmMove(float cm, float* speed)
{
    int pulseDistance = (cm * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    //Init des variables
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed [2] = {1,1};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit
    float speed1 = speed[0] / 25;
    float speed2 = speed[1] / 25;
    float ralentissement = 0;

    while ((ENCODER_Read(LEFT) < pulseDistance) && (ENCODER_Read(RIGHT) < pulseDistance))
    {
        delay(10 / speed2);
        if(ENCODER_Read(LEFT) < pulseDistance - PULSEPARTOUR)
        {
            if(speed1 < speed[0])
            {
                speed1 += speed[0] / 25;        //Accélération
                speed2 += speed[1] / 25;
            }
        }
        else
        {                                       //speed1 -= speed1/25;
            ralentissement += (0.005 /(ralentissement + speed1));    //Ralentissement
            ralentissement += (0.005 /(ralentissement + speed2));
            if(ralentissement > speed1)ralentissement = speed1;
            else if(ralentissement > speed2)ralentissement = speed2;
        } 
        
        lastLeft = newLeft;     //Enregistre les anciennes valeurs avant de relire
        lastRight = newRight;   
        newLeft = ENCODER_Read(LEFT);
        newRight = ENCODER_Read(RIGHT);
        //PRINT IN TERMINAL
            Serial.println("Left");
            Serial.println(speed2 * pSpeed[0]);
            Serial.println("Right");
            Serial.println(0 - (speed2 * pSpeed[1]));
            Serial.println(" ");
        //ADJUST AND SET SPEED
        AdjustSpeed(newLeft - lastLeft,newRight - lastRight,pSpeed, speed2);
        MOTOR_SetSpeed(LEFT, speed1 * pSpeed[0] - ralentissement);
        MOTOR_SetSpeed(RIGHT, speed2 * pSpeed[1] - ralentissement);
    }
    //TURN TO 0 MOTORS
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0); 
    speed[0] = speed1;
    speed[1] = speed2;  
}

/*
speed : speed entre 0 et 1 où 1 est 100%
huitTour : 1 = 1 huitieme de tour// 8 = 1 TOUR
direction : 0 = Gauche // 1 = Droit
*/
void TurnNoMoving(float speed, float huitTour, bool direction)
{
    int pulseDistance = (UnHuit * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed [2] = {1,1};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit
    if(direction)//Turn Right
    {
        while ((ENCODER_Read(LEFT) < pulseDistance) && (ENCODER_Read(RIGHT) > (0 - pulseDistance)))
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
            AdjustSpeed(newLeft - lastLeft, 0 - (newRight - lastRight),pSpeed, speed);
            MOTOR_SetSpeed(LEFT, speed * pSpeed[0]); //- pSpeed[0]);
            MOTOR_SetSpeed(RIGHT, (0 - speed) * pSpeed[1]);
        }
    }
    else
    {
        while ((ENCODER_Read(LEFT) > (0 - pulseDistance)) && (ENCODER_Read(RIGHT) < pulseDistance))
        {
            delay(20);
            lastLeft = newLeft;
            lastRight = newRight;
            newLeft = ENCODER_Read(LEFT);
            newRight = ENCODER_Read(RIGHT);          
            AdjustSpeed(0 - (newLeft - lastLeft),newRight - lastRight,pSpeed,speed);
            MOTOR_SetSpeed(LEFT, (0 - speed) * pSpeed[0]); //- pSpeed[0]);
            MOTOR_SetSpeed(RIGHT, speed * pSpeed[1]);
        }  
    }
    
     MOTOR_SetSpeed(RIGHT, 0);
     MOTOR_SetSpeed(LEFT, 0); 
}

void AdjustSpeed(int gauche, int droit, float* pSpeed, float speed)
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


void test(void)
{
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);

    MOTOR_SetSpeed(LEFT, 0.5);
    while(ENCODER_Read(LEFT) < 3200);



    //MOTOR_SetSpeed(RIGHT, 0.5);


    MOTOR_SetSpeed(RIGHT, 0);
    MOTOR_SetSpeed(LEFT, 0); 
}