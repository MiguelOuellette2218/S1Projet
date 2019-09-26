#include"MyIncludes.h"

void setup() {
  // put your setup code here, to run once:

  BoardInit();
  Serial.begin(9600);

  delay(1500);
}

void loop() 
{
  CmMove(100, 0.5);
  while(1);
}



