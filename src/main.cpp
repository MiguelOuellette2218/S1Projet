#include"MyIncludes.h"

void setup() {
  // put your setup code here, to run once:

  BoardInit();
  Serial.begin(9600);

  delay(1500);
}

void loop() 
{
  float speed[2] = {0.5,0.5};
  //Seq 1/**/
  CmMove(120, speed);
  TurnNoMoving(0.25,2,0);
  //Seq 2
  CmMove(90, speed);
  TurnNoMoving(0.25,2,1);
  //Seq 3
  CmMove(90, speed);
  TurnNoMoving(0.25,1,1);
  //Seq 4
  CmMove(150, speed);
  TurnNoMoving(0.25,2,0);

  CmMove(50, speed);
  TurnNoMoving(0.25,4,0);

  delay(2000);
  
}



