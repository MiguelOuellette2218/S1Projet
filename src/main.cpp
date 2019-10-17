#include"MyIncludes.h"

void setup() {
  // put your setup code here, to run once:

  BoardInit();
  Serial.begin(9600);

  delay(1500);
}

void Avancer(float distance)
{

float offset = (distance/50) * 5.88;
  float speed[2] = {0.7,0.7};
CmMove(distance-offset, speed);
  delay(200);

}

void Tourner(int angle)
{
if(angle == 45)
{
TurnNoMoving(0.2,1,DROITE);
  delay(200);
}

else if(angle == 90 )
{
TurnNoMoving(0.2,1,DROITE);
  delay(200);
  TurnNoMoving(0.2,1,DROITE);
  delay(200);
}

else if(angle == -45)
{
TurnNoMoving(0.2,1,GAUCHE);
  delay(200);
}

else if(angle == -90 )
{
 TurnNoMoving(0.2,1,GAUCHE);
  delay(200);
  TurnNoMoving(0.2,1,GAUCHE);
  delay(200);

}
else if(angle == 180 )
{
  TurnNoMoving(0.2,1,GAUCHE);
  delay(200);
  TurnNoMoving(0.2,1,GAUCHE);
  delay(200);
  TurnNoMoving(0.2,1,GAUCHE);
  delay(200);
  TurnNoMoving(0.2,1,GAUCHE);
  delay(200);
}
}

 void Stop()
 {
   MOTOR_SetSpeed(LEFT, 0); //- pSpeed[0]);
            MOTOR_SetSpeed(RIGHT, 0);
 }
void loop() 
{
  //float speed[2] = {0.7,0.7};
  
/*  Avancer(50);
Tourner(90);
Avancer(50);
Tourner(180);
 Avancer(50);
Tourner(-90);
Avancer(50);
Tourner(180);
  Stop();
delay(100000000);
*/



  Avancer(135);
Tourner(-90);
Avancer(110);
Tourner(90);
Avancer(45);
Tourner(90);
Avancer(60);
Tourner(-90);
Avancer(210);
Tourner(90);
Avancer(45);
Tourner(-90);
Avancer(135);

Tourner(180);

Avancer(135);
Tourner(90);
Avancer(45);
Tourner(-90);
Avancer(210);
Tourner(90);
Avancer(60);
Tourner(-90);
Avancer(45);
Tourner(-90);
Avancer(110);
Tourner(90);
Avancer(150);





Stop();
delay(100000000);
Tourner(90);
Tourner(90);
Stop();
delay(10000000);
Avancer(50);
Tourner(90);
Avancer(50);
Tourner(45);
Avancer(50);
Tourner(-90);
Avancer(50);
Tourner (-45);
Tourner(180);
  //Seq1
  //CmMove(122.5, speed);

  Avancer(122.5);

Tourner(-90);


 // TurnNoMoving(0.3,2,GAUCHE);
  //delay(200);
  
  //Seq2
  Avancer(90);
  //CmMove(90, speed);
  //delay(200);

  Tourner(90);
  //  TurnNoMoving(0.3,2,DROITE);
  //delay(200);

  //Seq3
  Avancer(74.5);
  //CmMove(74.5, speed);
  //delay(200);
 // TurnNoMoving(0.3,1,DROITE);
  Tourner(45);
 // delay(200);

  //Seq4

  Avancer(194.5);
 // CmMove(194.5, speed);
  //delay(200);

  Tourner (-90);
 // TurnNoMoving(0.3,2,GAUCHE);
 // delay(200);

  //Seq5
  Avancer(66.5);
  //CmMove(66.5, speed);
  //delay(200);
  Tourner(45);
 // TurnNoMoving(0.3,1,DROITE);
 // delay(200);

  //Seq6
  Avancer(100);
 // CmMove(100, speed);
 // delay(200);
 Tourner(180);
  //TurnNoMoving(0.3,4,DROITE);
 // delay(200);
}



