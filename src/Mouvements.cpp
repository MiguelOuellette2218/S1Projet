#include"MyIncludes.h"
#define ROBOTA 0.035
#define ROBOTB 0
#define USEROBOT ROBOTA

/*
* Fonction pour avancer
* float cm: Distance à parcourir
* float* speed: vitesse voulue
* bool (*callback)(void): fonction d'intéruption de la méthode
*/
void MoveFoward(float cm, float* speed, bool (*callback)(void))
{
    delay(200);
    int32_t pulseDistance = (cm * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    //Init des variables
    int time = 0;
    int oldTime = 0;
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed [2] = {0,0};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit
    float speedG = 0.1;//Partir lentement
    float speedD = 0.1;
    float ralentissement = 0;

    while ((ENCODER_Read(LEFT) < pulseDistance) || (ENCODER_Read(RIGHT) < pulseDistance))
    {
        time = millis();   
        if(time - oldTime > 49)
        {   
            // Fonction d'interruption
            if(callback) // Si l'adresse de calback est non NULL
                if(callback())
                    break;

            if(ENCODER_Read(LEFT) < pulseDistance - PULSEPARTOUR)
            {                                       //Accélération
                if(speedG + 0.05 < speed[0])speedG += 0.05;
                else speedG = speed[0];
                if(speedD + 0.05 < speed[1])speedD += 0.05;
                else speedD = speed[1];           
            }
            else
            {                                       //Ralentissement
                if(ralentissement < speedG - 0.30)ralentissement += 0.05 * (speedD + speedG);
            } 
            
            lastLeft = newLeft;     //Enregistre les anciennes valeurs avant de relire
            lastRight = newRight;   
            newLeft = ENCODER_Read(LEFT);
            newRight = ENCODER_Read(RIGHT);
            //ADJUST AND SET SPEED
            int erreurVitesse = (newLeft - lastLeft) - (newRight - lastRight);
            int erreurPosition = newLeft -  newRight;
            PID(erreurVitesse,erreurPosition, pSpeed, speedD);
            MOTOR_SetSpeed(LEFT, speedG + pSpeed[0] - ralentissement);
            MOTOR_SetSpeed(RIGHT, speedD + pSpeed[1] - ralentissement + USEROBOT);
            time = millis();
            oldTime = time;
        }
    }
    //TURN TO 0 MOTORS
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0); 
    speed[0] = speedG + pSpeed[0];
    speed[1] = speedD + pSpeed[1];  
}

void Turn(float* speed, float huitTour, bool direction)
{
    int pulseDistance = (UnHuit * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int time = 0;
    int oldTime = 0;
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed [2] = {0,0};//pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit
    float speedG, speedD;
    if(direction)
    {
        speedG = speed[0];//Partir lentement
        speedD = 0 - speed[1];
    }
    else
    {
        speedG = 0 - speed[0];//Partir lentement
        speedD = speed[1];
    }
    float ralentissement = 0;
    if(direction)//Turn Right
    {
        while ((ENCODER_Read(LEFT) < pulseDistance) && (ENCODER_Read(RIGHT) > (0 - pulseDistance)))
        {
            time = millis();   
            if(time - oldTime > 49)
            { 
                lastLeft = newLeft;
                lastRight = newRight;
                newLeft = ENCODER_Read(LEFT);
                newRight = ENCODER_Read(RIGHT);
                int erreurVitesse = (abs(newLeft) - abs(lastLeft)) - (abs(newRight) - abs(lastRight));
                int erreurPosition = abs(newLeft) -  abs(newRight);
                Serial.println(erreurVitesse);
                Serial.println(erreurPosition);
                Serial.println("_");
                PID(erreurVitesse,erreurPosition, pSpeed, speedD);
                //MOTOR_SetSpeed(LEFT, speed * pSpeed[0]); //- pSpeed[0]);
                //MOTOR_SetSpeed(RIGHT, (0 - speed) * pSpeed[1]);

                MOTOR_SetSpeed(LEFT, speedG - pSpeed[0]);
                MOTOR_SetSpeed(RIGHT,speedD + pSpeed[1] - USEROBOT);
            }
        }
    }
    else
    {
        while ((ENCODER_Read(LEFT) > (0 - pulseDistance)) && (ENCODER_Read(RIGHT) < pulseDistance))
        {
            time = millis();   
            if(time - oldTime > 49)
            { 
                lastLeft = newLeft;
                lastRight = newRight;
                newLeft = ENCODER_Read(LEFT);
                newRight = ENCODER_Read(RIGHT);    
                //ADJUST AND SET SPEED
                int erreurVitesse = (abs(newLeft) - abs(lastLeft)) - (abs(newRight) - abs(lastRight));
                int erreurPosition = abs(newLeft) -  abs(newRight);
                Serial.println(erreurVitesse);
                Serial.println(erreurPosition);
                Serial.println("_");
                PID(erreurVitesse,erreurPosition, pSpeed, speedD);
                //MOTOR_SetSpeed(LEFT, (0 - speed) * pSpeed[0]); //- pSpeed[0]);
                //MOTOR_SetSpeed(RIGHT, speed * pSpeed[1]);
                MOTOR_SetSpeed(LEFT,speedG - pSpeed[0]);
                MOTOR_SetSpeed(RIGHT,speedD + pSpeed[1] - USEROBOT);
            }
        }  
    }
    
     MOTOR_SetSpeed(RIGHT, 0);
     MOTOR_SetSpeed(LEFT, 0); 
        speed[0] = speedG + pSpeed[0];
        speed[1] = speedD + pSpeed[1];  
}

void PID(int erreurVitesse, int erreurPosition, float* pSpeed, float speed)
{
    static int oldErreurVitesse = 0;
    Serial.print("Erreur de vitesse ");
    Serial.println(erreurVitesse);
    Serial.print("Erreur de position ");
    Serial.println(erreurPosition);
    Serial.print("SG ");
    Serial.println(pSpeed[0],4);
    Serial.print("SD ");
    Serial.println(pSpeed[1],4);

    //Droit plus loin que gauche         
    if(erreurPosition < 0)//            D>G
    {       
        if(erreurVitesse > 0)//         #G>D#
        {//GOOD, en train de corrigé
            int x = 2;
            if(abs(erreurPosition) > abs(erreurVitesse))x = 0.5;
            pSpeed[1] -= (x*K * (abs(erreurPosition) - abs(erreurVitesse)));
            pSpeed[0] += (x*K * (abs(erreurPosition) - abs(erreurVitesse)));
            
            
        }     
        else//Pas good, doit corrigé
        {
           //Dans ce cas, il faut corrigé l'erreur de position et donc mettre une erreur dans la vitesse
            pSpeed[1] -= (K * abs(erreurPosition) + K * abs(erreurVitesse));
            pSpeed[0] += (K * abs(erreurPosition) + K * abs(erreurVitesse));
            Serial.println("D>Gcorrige");
        }
    }

    //Gauche plus loin que droit
    else if(erreurPosition > 0)//   G>D
    {
        if(erreurVitesse < 0)//     #D>G#
        {//GOOD
            int x = 2;
            if(abs(erreurPosition) > abs(erreurVitesse))x = 0.5;
            pSpeed[0] -= (x*K * (abs(erreurPosition) - abs(erreurVitesse)));
            pSpeed[1] += (x*K * (abs(erreurPosition) - abs(erreurVitesse)));        
        }
        else//pas good
        {
            //Dans ce cas, il faut corrigé l'erreur de position et donc mettre une erreur dans la vitesse
            pSpeed[0] -= (K * abs(erreurPosition) + K * abs(erreurVitesse));
            pSpeed[1] += (K * abs(erreurPosition) + K * abs(erreurVitesse));
            Serial.println("G>Dcorrige");
        }
    }
    oldErreurVitesse = erreurVitesse;
    Serial.println(".");
}