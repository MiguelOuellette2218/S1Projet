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

  //Seq1
  CmMove(122.5, speed);
  delay(200);
  TurnNoMoving(0.3,2,GAUCHE);
  delay(200);
  
  //Seq2
  CmMove(90, speed);
  delay(200);
  TurnNoMoving(0.3,2,DROITE);
  delay(200);

  //Seq3
  CmMove(74.5, speed);
  delay(200);
  TurnNoMoving(0.3,1,DROITE);
  delay(200);

  //Seq4
  CmMove(194.5, speed);
  delay(200);
  TurnNoMoving(0.3,2,GAUCHE);
  delay(200);

  //Seq5
  CmMove(66.5, speed);
  delay(200);
  TurnNoMoving(0.3,1,DROITE);
  delay(200);

  //Seq6
  CmMove(100, speed);
  delay(200);
  TurnNoMoving(0.3,4,DROITE);
  delay(200);
}



