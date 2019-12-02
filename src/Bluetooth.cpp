#include "MyIncludes.h"

using namespace std;

int Bluetooth()
{
    int Sortie = 0;  
    Serial.println("Bluetooth Send");

        Serial1.print("AT"); // (serial1) envoie AT au capteur.  le capteur recois AT qui est OK
        BluetoothRead(tableau);
       // Serial.print(tableau);
    for(int i=0; i<50; i++)tableau[i] = 0;      
        Serial1.print("AT+BAUD8");
        BluetoothRead(tableau);
       // Serial.print(tableau);
        Serial1.begin(115200);
        if(tableau[0] != 'O' || tableau[1] != 'K')Sortie = 1;
    for(int i=0; i<50; i++)tableau[i] = 0;  
        Serial1.print("AT+NAMEorusbt");
        BluetoothRead(tableau);
      //  Serial.print(tableau);
        if(tableau[0] != 'O' || tableau[1] != 'K')Sortie = 1;
    for(int i=0; i<50; i++)tableau[i] = 0; 
        Serial.println("Bluetooth Send");
        Serial1.print("AT"); // 
        BluetoothRead(tableau);
       // Serial.print(tableau);
        if(tableau[0] != 'O' || tableau[1] != 'K')Sortie = 1;
    for(int i=0; i<50; i++)tableau[i] = 0; 
    return Sortie;
}


void BluetoothRead(char* Tableau)
{
   
    int time = millis();
    int oldTime = time;
    for(int i = 0;time - oldTime < 1000;)
    {
        time = millis();
        if(Serial1.available())
        {
           Tableau[i] = Serial1.read();
           i ++;
        }
    }

}

int IsPaired()
{
     Serial1.print(10); 
     Serial.println("Demande de Pairage"); 
    Serial.println(ScanBluetooth()); 
}


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