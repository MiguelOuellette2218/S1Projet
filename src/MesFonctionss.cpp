
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
    float speedG = speed[0] / 25;//Partir lentement
    float speedD = speed[1] / 25;
    float ralentissement = 0;

    while ((ENCODER_Read(LEFT) < pulseDistance) && (ENCODER_Read(RIGHT) < pulseDistance))
    {
        delay(10 / speedD);
        
        if(ENCODER_Read(LEFT) < pulseDistance - PULSEPARTOUR)
        {
            if(speedG < speed[0])
            {
                speedG += speed[0] / 25;        //Accélération
                speedD += speed[1] / 25;
            }
        }
        else
        {                                       //speed1 -= speed1/25;
            ralentissement += (0.005 /(ralentissement + speedG));    //Ralentissement
            ralentissement += (0.005 /(ralentissement + speedD));
            if(ralentissement > speedG)ralentissement = speedG;
            else if(ralentissement > speedD)ralentissement = speedD;

       // if(ralentissement <speedG - 0.30 )ralentissement += 0.5 *(speedD + speedG);   

        } 
        
        lastLeft = newLeft;     //Enregistre les anciennes valeurs avant de relire
        lastRight = newRight;   
        newLeft = ENCODER_Read(LEFT);
        newRight = ENCODER_Read(RIGHT);
        //ADJUST AND SET SPEED
        int erreurInstant = (newLeft - lastLeft) - (newRight - lastRight);
        int erreurOLong = newLeft -  newRight;
        AdjustSpeed(erreurInstant,erreurOLong, pSpeed, speedD);
        MOTOR_SetSpeed(LEFT, speedG * pSpeed[0] - ralentissement);
        MOTOR_SetSpeed(RIGHT, speedD * pSpeed[1] - ralentissement);
    }
    //TURN TO 0 MOTORS
   // MOTOR_SetSpeed(LEFT, 0);
   // MOTOR_SetSpeed(RIGHT, 0); 
    speed[0] = speedG;
    speed[1] = speedD;  
}

/*
speed : speed entre 0 et 1 où 1 est 100%
huitTour : 1 = 1 huitieme de tour// 8 = 1 TOUR
direction : 0 = Gauche // 1 = Droit
*/
void TurnNoMoving(float speed, float huitTour, bool direction)
{
    float pulseDistance = 0;//(UnHuit * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed [2] = {1,1};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit
    int test = huitTour;
    switch (test)
    {
        case 1: 
            switch(direction)
            {
                case 0:
                pulseDistance = (7.05 * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
                break;
                case 1:
                pulseDistance = (7.2 * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
                break;
            }
            
        break;
        case 2:
            switch(direction)
            {
                case 0:
                pulseDistance = (9 * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
                break;
                case 1:
                pulseDistance = (8.1 * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
                break;
            }
        break;
        pulseDistance = (UnHuit * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
    }
    if(direction)//Turn Right
    {
        while ((ENCODER_Read(LEFT) < pulseDistance) && (ENCODER_Read(RIGHT) > (0 - pulseDistance)))
        {
            delay(20);
            lastLeft = newLeft;
            lastRight = newRight;
            newLeft = ENCODER_Read(LEFT);
            newRight = ENCODER_Read(RIGHT);
            Serial.println(newLeft - lastLeft);          
            Serial.println(0 - (newRight - lastRight)); 
            int erreurInstant = (newLeft - lastLeft) + (newRight - lastRight);
            int erreurOLong = newLeft +  newRight;        
            AdjustSpeed(erreurInstant, erreurOLong, pSpeed, speed);
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
            int erreurInstant = -(newLeft - lastLeft) - (newRight - lastRight);
            int erreurOLong = - newLeft -  newRight;    
            AdjustSpeed(erreurInstant,erreurOLong, pSpeed,speed);
            MOTOR_SetSpeed(LEFT, (0 - speed) * pSpeed[0]); //- pSpeed[0]);
            MOTOR_SetSpeed(RIGHT, speed * pSpeed[1]);
        }  
    }
    
     MOTOR_SetSpeed(RIGHT, 0);
     MOTOR_SetSpeed(LEFT, 0); 
}
/*

*/



void AdjustSpeed(int erreurInstant, int erreurOLong, float* pSpeed, float speed)
{
    int erreurCorrigeG = 1;
    int erreurCorrigeD = 1;
    if(erreurOLong < 0)//Gauche < Droit
    {
        if(pSpeed[1] > 1) erreurCorrigeD = (1 + 0.0005 * erreurOLong * speed);
        else erreurCorrigeG = (1 + -0.0005 * erreurOLong * speed);
    }
    else if(erreurOLong > 0)//Gauche > Droit
    {
        if(pSpeed[0] > 1) erreurCorrigeG = (1 - 0.0005 * erreurOLong * speed);
        else erreurCorrigeD = (1 + 0.0005 * erreurOLong * speed);
    }
    /*
    if(erreurOLong < 0)//Gauche < Droit
    {
        if(pSpeed[1] > 1) pSpeed[1] -= (-0.0001 * erreurOLong * speed);
        else pSpeed[0] += (-0.0001 * erreurOLong * speed);
    }
    else if(erreurOLong > 0)//Gauche > Droit
    {
        if(pSpeed[0] > 1) pSpeed[0] -= (0.0001 * erreurOLong * speed);
        else pSpeed[1] += (0.0001 * erreurOLong * speed);
    }
    //erreurInstant < 0         0 ou -2 ou -5 a tester  BEST: Vitesse
   if(erreurInstant < 0)//Gauche < Droit
    {   
 /* Si Droit est plus vite que la vitesse désiré, Ralentir le droit
    Sinon Accélere le gauche
        if(pSpeed[1] > 1)erreurCorrigeD = (erreurCorrigeD + (1 - 0.0001 * erreurInstant))/2;
        else erreurCorrigeG = (erreurCorrigeG + ( 1 + 0.0001 * erreurInstant))/2;
    }
    else if(erreurInstant > 0)//Droit trop rapide
    {
        if(pSpeed[0] > 1)erreurCorrigeG = (erreurCorrigeG + (1 - 0.0001 * erreurInstant))/2;
        else erreurCorrigeD = (erreurCorrigeD + (1 + 0.0001 * erreurInstant))/2;
    }*/
    pSpeed[0] = erreurCorrigeG;
    pSpeed[1] = erreurCorrigeD;
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