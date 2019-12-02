#include "MyIncludes.h"

void setup()
{
  // put your setup code here, to run once:
  BoardInit();
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1500);
  SetupSonar();
  Bluetooth();
}

void loop()
{

  //ScanBluetooth();

  //delay(100);

  if (ROBUS_IsBumper(0)) // Bumper gauche
  {
   // ParcourirBloc(100);
    
  }
  if (ROBUS_IsBumper(1)) // Bumper droite
  {
   // ParcourirBloc(100);
   // Serial.println("Fin de parcour"); 
  }
  //  IsPaired();
   
  if (modeDeplacement == 0)
  {
    ModeBluetooth();
  }
  else
  {
    ModeAutomatisee();
  }


 
}

int mainbumper()
{
  if (ROBUS_IsBumper(2)) //Bumper Avant
  {
    AX_BuzzerON(1000, 400);
    return 2;
  }
  if (ROBUS_IsBumper(3)) //Bumper arrière
  {
    AX_BuzzerON(1000, 400);
    return 3;
  }
  if (ROBUS_IsBumper(0)) // Bumper gauche
  {
    AX_BuzzerON(1000, 400);
    return 0;
  }
  if (ROBUS_IsBumper(1)) // Bumper droite
  {
    AX_BuzzerON(1000, 400);
    return 1;
  }
  delay(200);
  return -1;
}
