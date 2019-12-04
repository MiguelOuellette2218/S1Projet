#include "MyIncludes.h"
using namespace std;

    /*
    * Fonction qui permet d'initialiser le module bluetooth , doit être appeler dans le setup
    */
int Bluetooth()
{
    int Sortie = 0;
    Serial.println("Bluetooth Send");

    Serial1.print("AT"); // (serial1) envoie AT au capteur.  le capteur recois AT qui est OK
    BluetoothRead(tableau);
    // Serial.print(tableau);
    for (int i = 0; i < 50; i++)
        tableau[i] = 0;
    Serial1.print("AT+BAUD8");
    BluetoothRead(tableau);
    // Serial.print(tableau);
    Serial1.begin(115200);
    if (tableau[0] != 'O' || tableau[1] != 'K')
        Sortie = 1;
    for (int i = 0; i < 50; i++)
        tableau[i] = 0;
    Serial1.print("AT+NAMEorusbt");
    BluetoothRead(tableau);
    //  Serial.print(tableau);
    if (tableau[0] != 'O' || tableau[1] != 'K')
        Sortie = 1;
    for (int i = 0; i < 50; i++)
        tableau[i] = 0;
    Serial.println("Bluetooth Send");
    Serial1.print("AT"); //
    BluetoothRead(tableau);
    // Serial.print(tableau);
    if (tableau[0] != 'O' || tableau[1] != 'K')
        Sortie = 1;
    for (int i = 0; i < 50; i++)
        tableau[i] = 0;
    return Sortie;
}

    /*
    * Fonction qui fait permet de lire le module bluetooth en attente d'initialisation 
    */
void BluetoothRead(char *Tableau)
{

    int time = millis();
    int oldTime = time;
    for (int i = 0; time - oldTime < 1000;)
    {
        time = millis();
        if (Serial1.available())
        {
            Tableau[i] = Serial1.read();
            i++;
        }
    }
}

    /*
    * Fonction qui permet de savoir si le module est Paired ou non NON-FONCTIONNEL
    */
int IsPaired()
{
    Serial1.print(10);
    Serial.println("Demande de Pairage");
    Serial.println(ScanBluetooth());
}

    /*
    * Fonction qui permet d'obtenir les informations contenu dans le module bluetooth 
    */
void LireBluetooth()
{
    for (int i = 0; i < 50; i++)
    {
        if (Serial1.available())
        {
            tableau[i] = Serial1.read();
            i++;
        }
    }
}

    /*
    * Fonction qui permet de recuperer les informations envoyer a partir de l'application
    */
int ScanBluetooth()
{
    if (Serial1.available())
    {
        LireBluetooth();
        int output;

        //  String sortie = str(tableau);
        //Serial.print(sortie);
        //output=  Integer.parseInt(tableau);

        //tableau.
        sscanf(tableau, "%d", &output);

        for (int i = 0; i < 50; i++)
            tableau[i] = 0;

        //Serial.print(output);

        Serial.print(output);
        return output;
    }
    else
    {
        return 0;
    }
}