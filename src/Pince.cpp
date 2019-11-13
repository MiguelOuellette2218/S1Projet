#include "MyIncludes.h"

//Ferme la pince ,doit avoir setupPince() avant d'utiliser cette fonction
void fermerPinces()
{
    SERVO_SetAngle(0, 90);
}

//Ouvre la pince ,doit avoir setupPince() avant d'utiliser cette fonction
void ouvrirPinces()
{
    SERVO_SetAngle(0, 135);
}

//Instancie les propriété de la pince pour etre utiliser plus tard
void setupPinces()
{
    SERVO_Enable(0);
    delay(200);
    ouvrirPinces();
}

//Ferme la Gate ,doit avoir setupGate() avant d'utiliser cette fonction
void fermerGate()
{
    SERVO_SetAngle(1, 90);
}

//Ouvre la Gate ,doit avoir setupGate() avant d'utiliser cette fonction
void ouvrirGate()
{
    SERVO_SetAngle(1, 0);
}

//Instancie les propriété de la gate pour etre utiliser plus tard
void setupGate()
{
    SERVO_Enable(1);
    delay(200);
    ouvrirGate();
}