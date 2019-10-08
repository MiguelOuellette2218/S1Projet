#include"MyIncludes.h"

void setup() {
  // put your setup code here, to run once:

  BoardInit();
  Serial.begin(9600);

  delay(1500);
}

void loop() 
{
  float speed[2] = {0.7,0.7};
  /*CmMove(50, speed);
  TurnNoMoving(0.15,1,0);
  */
  //Seq 1
  CmMove(120, speed);
  TurnNoMoving(0.3,2,0);
  //Seq 2
  CmMove(90, speed);
  TurnNoMoving(0.3,2,1);
  //Seq 3
  CmMove(95, speed);
  TurnNoMoving(0.3,1,1);
  //Seq 5
  CmMove(175, speed);
  TurnNoMoving(0.3,2,0);
  //Seq 6
  CmMove(71, speed);
  TurnNoMoving(0.3,1,1);
  //Seq 7
  CmMove(100, speed);
  TurnNoMoving(1,24,1);
  while(1);
}



