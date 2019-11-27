#include "MyIncludes.h"
#include <math.h>

float ConvertBitToDist(float input)
{
    double voltage = (input*5)/1023;

    double dist = -13.632*pow(voltage,6) 
    + 101.03*pow(voltage, 6)
    - 246*pow(voltage,4) 
    + 135.61*pow(voltage, 3)
     + 317.15*pow(voltage, 2) +
     499.1*voltage + 227.22;

    return dist;
}

int comparateurIR()
{   
    
    float distanceD = ConvertBitToDist(ROBUS_ReadIR(0));
    float distanceG = ConvertBitToDist(ROBUS_ReadIR(1));
  
    float capteurIRG = distanceG;
    float capteurIRD = distanceD;
    Serial.println(distanceG);
    Serial.println(distanceD);
    //Serial.println("##########");
    // code qui compare la valeur de chaque capteur infrarouge mais qui laisse un dead zone 

    // les deux capteurs captent la meme distance
    if (distanceD == distanceG)
    {
        return 0; 
    }

    // le cote droit est plus loin du mur
    if (distanceD > distanceG)
    {
        return -1;
    }

    // le cote droit est plus proche du mur
    if (distanceD < distanceG )
    {
        return -2; 
    }
    
}


void mouvementIR ()
{
    if(PersonneDevant())
    {
        MOTOR_SetSpeed(0,0);
        MOTOR_SetSpeed(1,0);
    }
    else
    {

    //definir la vitesse desirer pour utiliser la fonction 
    int comparaison = comparateurIR(); //Lecture des distances

    // les deux sensors lisent la meme chose 
    while (comparaison == 0)
    {   
        //avancerCm(20, 5, NULL);
           MOTOR_SetSpeed(0,0.3);
        MOTOR_SetSpeed(1,0.3);
        comparateurIR();
    }
    
    // le capteur droit est plus proche
    while (comparaison == -2)
    {   
        
        MOTOR_SetSpeed(0,0.3);
        MOTOR_SetSpeed(1,0.32);
        delay(50);
       // MOTOR_SetSpeed(1,0);
       // MOTOR_SetSpeed(0,0);
        comparateurIR();
        
        
    }
    // le capteur gauche est plus proche
    while (comparaison == -1)
    {
        
        MOTOR_SetSpeed(0,0.32);
        MOTOR_SetSpeed(1,0.3);
        delay(50);
       // MOTOR_SetSpeed(1,0);
        //MOTOR_SetSpeed(0,0);
        comparateurIR();
      
        }
    }
}

int PersonneDevant()
{
    int capteur_sonar = SONAR_GetRange(0);
    
    Serial.println(capteur_sonar);
    //Serial.println("##########");
    
    if(capteur_sonar > distancePersonne)
        return 0;

    else if (capteur_sonar < distancePersonne)
        return 1;

}
/* 
void mvmt_sonar()
{   

    distance_Sonar();
    while (distance_Sonar() == 0)
    {
        mouvementIR ();
        distance_Sonar();
    }

    while (distance_Sonar() == -1)
    {
        MOTOR_SetSpeed(1,0);
        MOTOR_SetSpeed(0,0);
        distance_Sonar();

    }



}

*/
