#include"MyIncludes.h"

#define CIRCONFERENCE 24.25

void setup() {
  // put your setup code here, to run once:

  BoardInit();
  Serial.begin(9600);  
}

void loop() {
  //Serial.println(ROBUS_ReadIR(2));
  DecisionDirection();
  delay(200);
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
