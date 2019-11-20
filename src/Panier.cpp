#include "MyIncludes.h"

int comparateurIR()
{
    int capteurIRG = ROBUS_ReadIR(0);
    int capteurIRD = ROBUS_ReadIR(1);
   //Serial.println(capteurIRG);
   //Serial.println(capteurIRD);
    //Serial.println("##########");
    // code qui compare la valeur de chaque capteur infrarouge mais qui laisse un dead zone 

    // les deux capteurs captent la meme distance
    if (capteurIRD == capteurIRG)
    {
        return 0; 
    }

    // le cote droit est plus proche du mur
    if (capteurIRD < (capteurIRG + 100))
    {
        return -1;
    }

    // le cote droit est plus loin du mur
    if (capteurIRD > (capteurIRG + 100))
    {
        return -2; 
    }
    
}

void mouvementIR ()
{
    //definir la vitesse desirer pour utiliser la fonction 
    comparateurIR(); //Lecture des distances

    // les deux sensors lisent la meme chose 
    while (comparateurIR() == 0)
    {   
        avancerCm(20, 5, NULL);
        comparateurIR();
    }
    
    // le capteur droit est plus proche
    while (comparateurIR() == -2)
    {   
        
        MOTOR_SetSpeed(0,0.3);
        MOTOR_SetSpeed(1,0.35);
        delay(500);
        MOTOR_SetSpeed(1,0);
        MOTOR_SetSpeed(0,0);
        comparateurIR();
        
        
    }
    // le capteur gauche est plus proche
    while (comparateurIR() == -1)
    {
        
        MOTOR_SetSpeed(0,0.35);
        MOTOR_SetSpeed(1,0.3);
        delay(500);
        MOTOR_SetSpeed(1,0);
        MOTOR_SetSpeed(0,0);
        comparateurIR();
      
        
    }
}

int distance_Sonar()
{
    int capteur_sonar = SONAR_GetRange(0);
    
    Serial.println(capteur_sonar);
    Serial.println("##########");
    
    if(capteur_sonar > 30)
        return 0;

    else if (capteur_sonar < 30)
        return -1;

}

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
