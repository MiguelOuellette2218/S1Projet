#include"MyIncludes.h"

#define CIRCONFERENCE 24.25

void constanteSettings();

void setup() {
  // put your setup code here, to run once:

  BoardInit();

  Serial.begin(9600);

  delay(1500);
}

void loop() {

  //constanteSettings();

  avancerCm(112, 2.5);
  tournerSurUneRoue(LEFT, 90, 1);
  avancerCm(77, 2.5);
  tournerSurUneRoue(RIGHT, 90, 1);
  avancerCm(100, 2.5);
  tournerSurUneRoue(RIGHT, 45, 1);
  avancerCm(164, 5);
  tournerSurUneRoue(LEFT, 90, 1);
  avancerCm(63, 2.5);
  tournerSurUneRoue(RIGHT, 45, 1);
  avancerCm(100, 2.5);

  tournerSurLuiMeme(180, 2);

  avancerCm(100, 2.5);
  tournerSurUneRoue(LEFT, 45, 1);
  avancerCm(63, 2.5);
  tournerSurUneRoue(RIGHT, 90, 1);
  avancerCm(164, 5);
  tournerSurUneRoue(LEFT, 45, 1);
  avancerCm(100, 2.5);
  tournerSurUneRoue(LEFT, 90, 1);
  avancerCm(77, 2.5);
  tournerSurUneRoue(RIGHT, 90, 1);
  avancerCm(112, 2.5);

  delay(1500);
}

void constanteSettings()
{
  float kp = 0.000009;

  if (ROBUS_IsBumper(2)) //Bumper Avant
  {

  }
  if (ROBUS_IsBumper(3)) //Bumper arrière
  {
    avancerCm(200, 5);
  }
  if (ROBUS_IsBumper(0)) // Bumper gauche
  {
    kp += 0.00001;
    avancerCm(100, 2.5);
  }
  if (ROBUS_IsBumper(1)) // Bumper droite
  {
    kp -= 0.00001;
    avancerCm(100, 2.5);
  }
  delay(200);
}



