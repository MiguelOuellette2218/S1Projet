#include"MyIncludes.h"

#define CIRCONFERENCE 24.25

void setup() {
  // put your setup code here, to run once:

  BoardInit();

  Serial.begin(9600);

  delay(1500);
}

void loop() {

  constanteSettings();
  /*
  avancerCm(100);
  delay(200);
  tournerSurUneRoue(LEFT, 90);
  delay(200);
  avancerCm(100);
  delay(200);
  tournerSurUneRoue(LEFT, 90);
  delay(200);
  avancerCm(100);
  delay(200);
  tournerSurUneRoue(LEFT, 90);
  delay(200);
  avancerCm(100);
  */

  //avancerCm(120);
  //TurnNoMoving(0.25,4,0);
}

void constanteSettings()
{
  if (ROBUS_IsBumper(2)) //Bumper Avant
  {

  }
  if (ROBUS_IsBumper(3)) //Bumper arrière
  {
    
  }
  if (ROBUS_IsBumper(0)) // Bumper gauche
  {

  }
  if (ROBUS_IsBumper(1)) // Bumper droite
  {

  }
  delay(200);
}



