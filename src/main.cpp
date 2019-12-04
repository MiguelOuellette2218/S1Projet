#include "MyIncludes.h"
int blah = 0;
int* modeDeplacement = &blah;

void setup()
{
  // put your setup code here, to run once:
  BoardInit();
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1500);
  SetupSonar();
  Bluetooth();
  *modeDeplacement = 0;
  Serial.println(*modeDeplacement);
}

void loop()
{
//float capteur_sonar = SONAR_GetRange(1);
    
    //Serial.println(capteur_sonar);

  //modeDeplacement = 1;

  //Serial.println(*modeDeplacement);
  if (*modeDeplacement == 0)
  {
    ModeBluetooth(modeDeplacement);
    //Serial.println(*modeDeplacement);
        
  }
  else
  {
    ModeAutomatisee(modeDeplacement);
    //Serial.println(*modeDeplacement);  
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
