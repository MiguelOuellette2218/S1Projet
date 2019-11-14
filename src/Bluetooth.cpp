#include "MyIncludes.h"

void Bluetooth()
{
    Serial.println("Bluetooth Send");
    Serial1.print("AT"); // (serial1) envoie AT au capteur.  le capteur recois AT qui est OK
    char tableau[50] = {0};
    BluetoothRead(tableau);
    Serial.print(tableau);
    

    for(int i=0; i<50; i++)tableau[i] = 0;      
        Serial1.print("AT+BAUD8");
        BluetoothRead(tableau);
        Serial.print(tableau);
        Serial1.begin(115200);
    for(int i=0; i<50; i++)tableau[i] = 0;  
        Serial1.print("AT+NAMEorusbt");
        BluetoothRead(tableau);
        Serial.print(tableau);


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