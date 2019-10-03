#include"MyIncludes.h"

void setup() {
  // put your setup code here, to run once:

  BoardInit();
  Serial.begin(9600);

  delay(1500);
}

void loop() 
{
  //CmMove(200, 0.5);
  TurnNoMoving(0.25,8,1);
  delay(2000);
  
}



