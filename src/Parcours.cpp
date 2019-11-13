#include "MyIncludes.h"

void FaireParcoursCombattantA(COULEUR couleur)
{
    /*bool (*p_detectionLigne)(void);
    p_detectionLigne = detectionLigne;*/

    switch (couleur)
    {
    case ROUGE:
        //Tourne a gauche pour être en angle de 45 par rapport au but vert
        // avancerCm(100 , 2, NULL);
        //tournerSurLuiMeme(RIGHT, 90 ,1);
        break;

    case VERT:
        //Tourne a gauche pour être en angle de 45 par rapport au but rouge
        //avancerCm(100 , 2, NULL);
        // tournerSurLuiMeme(LEFT, 90 ,1);
        break;

    case BLEU:
        //Tourne a droit pour être en angle de 45 par rapport au but bleu
        //tournerSurLuiMeme(RIGHT, 90 ,1);
        break;

    case JAUNE:
        //Tourne a gauche pour être en angle de 45 par rapport au but jaune
        tournerSurLuiMeme(LEFT, 90, 1);
        avancerCm(42, 3, NULL);
        tournerSurLuiMeme(LEFT, 45, 1);
        break;

    default:
        break;
    }

    //Avancer jusqu'a trouver un ligne blanche**hardcode finalement
    ouvrirGate();
    avancerCm(70, 5, NULL);
    fermerGate();
    delay(1000);

    //Reculer pour revenir vers la ligne
    reculerCm(40, 2, NULL);
    tournerSurLuiMeme(RIGHT, 180, 1);
    avancerCm(75, 5, NULL);

    //DecisionDirection();

    //Dropper la balle dans le centre
    ouvrirGate();
    delay(1000);

    //DECALISSÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉ
    reculerCm(40, 4, NULL);
}

void FaireParcoursCombattantB(COULEUR couleur)
{
    float speed[2] = {0.3, 0.3};
    //Attendre le temps que le premier robot fasse sa job
    //delay(1000*60);
    //MoveFoward(15, speed , false);
    //avancerCm(15,1,false);
    //Scan pour la balle
    float tourne = 0;
    ScannerPourBalle();
    /*
if(dist == 0)
{
    tournerSurLuiMeme(LEFT, 30 ,false);
    delay(1000);
    avancerCm(20,1,false);
    delay(1000);
    ScannerPourBalle();
}
*/
    //moteurInverse()
    //delay(500);
    fermerGate();
    /*ENCODER_ReadReset(LEFT);
ENCODER_ReadReset(RIGHT);
if(tourne > 0)
{
    Serial.println("tourne > 0");
     Serial.println(tourne);
    MOTOR_SetSpeed(LEFT, -0.3);
    MOTOR_SetSpeed(RIGHT, 0.3);
    while(ENCODER_Read(RIGHT) < tourne);
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
}
else
{
     Serial.println("tourne < 0");
     Serial.println(tourne);
    MOTOR_SetSpeed(LEFT, 0.3);
    MOTOR_SetSpeed(RIGHT,-0.3);
    while(ENCODER_Read(RIGHT) > tourne);
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0); 
}

*/

    delay(500);
    //MoveFoward(7,speed,false);
    avancerCm(7, 1, false);
    delay(500);
    switch (couleur)
    {
    case ROUGE:
        //Tourne a droite pour etre en angle de 135 par rapport au but rouge
        tournerSurLuiMeme(RIGHT, 135, 1);
        break;
    case VERT:
        //Tourne a gauche pour être en angle de 135 par rapport au but vert
        tournerSurLuiMeme(LEFT, 135, 1);
        break;
    case BLEU:
        //Tourne a droit pour être en angle de 45 par rapport au but bleu
        //tournerSurLuiMeme(RIGHT, 90 ,1);
        tournerSurLuiMeme(LEFT, 45, 1);
        break;
    case JAUNE:
        //Tourne a gauche pour être en angle de 45 par rapport au but jaune
        tournerSurLuiMeme(RIGHT, 45, 1);
        break;
    }
    delay(500);
    //MoveFoward(122,speed , false);
    avancerCm(100, 5, false);
    delay(500);
    ouvrirGate();

    avancerCm(50, 5, false);
    delay(500);
    //reculerCm(100,5,false);

    //PArt a course pour le yeet dans un but
    //BallonChasseur(couleur);
}

void ScannerPourBalle()
{
    // tournerSurLuiMeme(-90, 1);
    // tourner a 45 degrée
    float pSpeed[2] = {0.3, 0.3};
    TurnNoMoving(.5, 1, 0);

    //ENCODER_Reset(LEFT);
    //int32_t pulse_LEFT = 0;
    //int distanceTourner = 0;

    //TurnNoMoving()

    int incrementAngle = 36;

    float distanceCapteur = (-0.0943 * ROBUS_ReadIR(1)) + (float)56.5 - 10;

    //float voltage = (ROBUS_ReadIR(1)/1023) * 5;

    //float distanceCapteur = fabs(19.57/(voltage- 0.2602));

    //float distanceCapteur = (-0.0943*ROBUS_ReadIR(1)) + (float)56.5 - 10;
    //float AnciennedistanceCapteur = distanceCapteur;

    float difference = 30;

    float anglePetit = (float)180 / incrementAngle;

    anglePetit = anglePetit / (float)45;

    MOTOR_SetSpeed(LEFT, 0.2);
    MOTOR_SetSpeed(RIGHT, -0.2);
    for (size_t i = 0; i < (incrementAngle / 10) * 12; i++)
    {
        //Attribue l'ancienne valeur de distance à une variable puis change la valeur de la distance du présent
        //AnciennedistanceCapteur = distanceCapteur;

        //voltage = (ROBUS_ReadIR(1)/1023) * 5;

        distanceCapteur = (-0.0943 * ROBUS_ReadIR(1)) + (float)56.5 - 10;
        // Serial.println("Distance");
        // Serial.println(distanceCapteur);
        //pulse_LEFT = ENCODER_Read(LEFT);
        //*Tourne = pulse_LEFT/2;
        //Trouve si l'ancienne distance par rapport a la nouvelle est trop differente (donc qu'il y a probablement un object devant lui)
        if (distanceCapteur < difference)
        {
            //MoveFoward(distanceCapteur,50 ,false);
            MOTOR_SetSpeed(LEFT, 0);
            MOTOR_SetSpeed(RIGHT, 0);
            delay(100);

            // TurnNoMoving(0.3,0.1,1);
            // delay(500);
            MoveForward(distanceCapteur * 1.5, pSpeed, 0);
            // distanceTourner = (int)(pulse_LEFT*CIRCONFERENCE/PULSEPARTOUR);
            //  //TurnNoMoving(.5, anglePetit*2, 1);
            //delay(200);
            //avancerCm(distanceCapteur + 5, 0.5);

            // Serial.println("Distance Trouver !");
            // Serial.println(distanceCapteur);
            // MoveFoward(distanceCapteur,pSpeed ,0);
            //  avancerCm(distanceTourner,1,false);

            //return distanceTourner;
            return;
            break;
        }
        else
        {
            //tournerSurLuiMeme((int)10,(float)200);
            //TurnNoMoving(.5, anglePetit, 1);
            // distanceTourner = 0;
        }

        delay(50);
    }
    TurnNoMoving(.5, 1.2, 0);
    delay(500);
    avancerCm(10, 0.5, false);
    delay(500);
    //TurnNoMoving()
    ScannerPourBalle();

    //  MOTOR_SetSpeed(LEFT, 0);
    //  MOTOR_SetSpeed(RIGHT, 0);
    //  return distanceTourner;
}