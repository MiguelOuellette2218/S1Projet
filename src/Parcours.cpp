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
    float tourne = 0;
    ScannerPourBalle();
    fermerGate();

    delay(500);
 
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
}

void ScannerPourBalle()
{
    float pSpeed[2] = {0.3, 0.3};
    TurnNoMoving(.5, 1, 0);

    int incrementAngle = 36;

    float distanceCapteur = (-0.0943 * ROBUS_ReadIR(1)) + (float)56.5 - 10;

    float difference = 30;

    float anglePetit = (float)180 / incrementAngle;

    anglePetit = anglePetit / (float)45;

    MOTOR_SetSpeed(LEFT, 0.2);
    MOTOR_SetSpeed(RIGHT, -0.2);
    for (size_t i = 0; i < (incrementAngle / 10) * 12; i++)
    {    

        distanceCapteur = (-0.0943 * ROBUS_ReadIR(1)) + (float)56.5 - 10;
      
        //Trouve si l'ancienne distance par rapport a la nouvelle est trop differente (donc qu'il y a probablement un object devant lui)
        if (distanceCapteur < difference)
        {
            //MoveFoward(distanceCapteur,50 ,false);
            MOTOR_SetSpeed(LEFT, 0);
            MOTOR_SetSpeed(RIGHT, 0);
            delay(100);

            MoveForward(distanceCapteur * 1.5, pSpeed, 0);
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

}

//Fonction qui est appeler lorsqu'on clique sur le bouton panique sur le telephone
void ModePanique()
{
    for (size_t i = 0; i < 6; i++)
    {
        AX_BuzzerON(1000, 200);
        delay(100);
    }
}

//Mode de deplacement lorsque le mode de communication par bluetooth est activé
//Cette fonction va être appeler à chaque loop pour prendre des decisions
void ModeBluetooth()
{
    int input = ScanBluetooth();
    if (input != 0)
    {
        if (input == 1)
        {
            //Aller au prochain point           
             Serial.print("SENS NORMAL");
            ParcourirProchainBloc(0);
        }
        else if (input == 2)
        {
             Serial.println("SENS INVERSE");
            ParcourirProchainBloc(1);
        }
        //PANIC
        else if (input == 4)
        {
             Serial.print("PPPPPAAAAANNNNNNIIIIIICCCCC");
            ModePanique();
        }
        //MODE AUTONOME
        else if (input == 5)
        {
            Serial.print("MODE Autonome");
            modeDeplacement = 1;
        }
        //MODE BLUETOOTH
        else if (input == 6)
        {
            Serial.print("MODE BLUETOOTH");
            modeDeplacement = 0;
        }
    }
}

//Mode de deplacement lorsque le mode de communication par bluetooth est desactivé
//Cette fonction va être appeler à chaque loop pour prendre des decisions basé sur le mode automatisé
void ModeAutomatisee()
{
    int input = ScanBluetooth();

    ParcourirProchainBloc(0);
    if (input != 0)
    {    
        //PANIC
         if (input == 4)
        {
             Serial.print("PPPPPAAAAANNNNNNIIIIIICCCCC");
            ModePanique();
        }
        //MODE AUTONOME
        else if (input == 5)
        {
            Serial.print("MODE Autonome");
            modeDeplacement = 1;
        }
        //MODE BLUETOOTH
        else if (input == 6)
        {
            Serial.print("MODE BLUETOOTH");
            modeDeplacement = 0;
        }
    }
}

//Fonction qui permet d'aller au prochain bloc dans le parcours final ,à
// une direction de 0 s'ignifie dans la direction normal
//une directon de -1 s'ignifie dans la direction opposé
void ParcourirProchainBloc(int direction)
{
    //TODO:
        //Implementer le tableau de distance
        //Implementer les virages ainsi que les direction differentes
        if(direction!=directionRobot)
        {
            tournerSurLuiMeme(1, 180, 1);
            directionRobot = direction;
            delay(200);
        }    
  
        if(tableauEmplacement[emplacement-direction] == 1 )
        {
          tournerSurLuiMeme(0, 90,1);
            emplacement = emplacement+1;
            delay(200);
        }
        else if(tableauEmplacement[emplacement-direction] == 2 )
        {
          tournerSurLuiMeme(1, 90,1);
          emplacement = emplacement+1;
            delay(200);
        }
        ParcourirBloc(tableauEmplacement[emplacement-direction]);
        delay(200);

    //Serial.println(tableauEmplacement[emplacement-direction]);
    // avancerCm(tableauEmplacement[emplacement-direction],1,0);
        emplacement = emplacement+1;
    
}