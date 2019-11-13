#include "MyIncludes.h"

int IdentifierPossibilite(float volt)
{
    /*
Possibilité possible du captage du voltage du circuit , le premier chiffre étant l'état du capteur de gauche , le 2e étant celui du milieu et le 3e etant celui du 
000 0.03 
001 1.44 
010 0.75  
011 2.16  
100 2.85
101 4.25
110 3.57
111 4.95
*/

    // Pour robot avec pince
    float possibilite[8] = {2.16, 3.52, 4.22, 0.74, 2.79, 0.2, 1.44, 4.8};

    float difference = 0.2;

    //bool capteurGauche =false;
    // capteurMilieu = false;
    //bool capteurDroit = false;

    for (unsigned int i = 0; i < sizeof(possibilite) / 4; i++)
    {
        // Si le voltage entré est plus ou moin grand à chacune des possibilite
        // (pour laisser de la place à un jeu parce que le analogue n'est pas très précis)
        if (volt > possibilite[i] - difference && volt < possibilite[i] + difference)
        {
            return i;
        }
    }

    return 10;
}

bool DecisionDirection()
{
    bool breaker = false;
    static int counter = 0;

    //Initialisation du pointeur récursif
    //bool (*p_DecisionDirection)(void);
    //p_DecisionDirection = DecisionDirection;

    int possibilite = IdentifierPossibilite((float)(analogRead(A0) * (5.0 / 1023.0)));

    switch (possibilite)
    {
    case 0:
        // Tourner à gauche légèrement
        MOTOR_SetSpeed(LEFT, 0.4);
        MOTOR_SetSpeed(RIGHT, 0.5);
        counter = 0;
        break;
    case 1:
        // Tout droit way to go
        MOTOR_SetSpeed(LEFT, 0.5);
        MOTOR_SetSpeed(RIGHT, 0.5);
        counter = 0;
        break;
    case 2:
        // Tourner à droite légèrement
        MOTOR_SetSpeed(LEFT, 0.5);
        MOTOR_SetSpeed(RIGHT, 0.4);
        counter = 0;
        break;
    case 3:
        // Tourner à gauche aggressivement
        MOTOR_SetSpeed(LEFT, 0.35);
        MOTOR_SetSpeed(RIGHT, 0.5);
        counter = 0;
        break;
    case 4:
        // Tourner à droite aggressivement
        MOTOR_SetSpeed(LEFT, 0.5);
        MOTOR_SetSpeed(RIGHT, 0.35);
        counter = 0;
        break;
    /*case 5:
            // HELP
            //AX_BuzzerON(1000, 5000);
            //Serial.println("HELP");
            MOTOR_SetSpeed(LEFT, 0);
            MOTOR_SetSpeed(RIGHT, 0);
            break;
        case 6:
            // HELP
            //AX_BuzzerON(1000, 5000);
            //Serial.println("HELP");
            MOTOR_SetSpeed(LEFT, 0);
            MOTOR_SetSpeed(RIGHT, 0);
            break;
        case 7:
            // HELP
            //AX_BuzzerON(1000, 5000);
            //Serial.println("HELP");
            MOTOR_SetSpeed(LEFT, 0);
            MOTOR_SetSpeed(RIGHT, 0);
            break;*/
    default:
        //AX_BuzzerON(1000, 5000);
        //Serial.println("HELP");
        counter++;
        if (counter >= 3)
        {
            counter = 0;
            MOTOR_SetSpeed(LEFT, 0);
            MOTOR_SetSpeed(RIGHT, 0);
        }
        break;
    }
    //Serial.print("Counter : ");
    //Serial.println(counter);
    return breaker;
}

/*
* Fonction qui détecte la présence d'une ligne
* Retourne true si il trouve une ligne false s'il ne trouve rien  
*/
bool detectionLigne()
{
    if (IdentifierPossibilite((float)(analogRead(A0) * (5.0 / 1023.0))) != 7)
        return true;

    return false;
}
