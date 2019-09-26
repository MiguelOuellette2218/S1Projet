#include"MyIncludes.h"

void setup() {
  // put your setup code here, to run once:

  BoardInit();

  pinMode(PIN13 , OUTPUT); 
  Serial.begin(9600);

  delay(1500);
}

void loop() {
  //CmMove(100, 0.5);
  if (ROBUS_IsBumper(2))
  {
    MOTOR_SetSpeed(0, -0.5);
    MOTOR_SetSpeed(1, -0.5);
    delay(4000);
    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);
  }
  if (ROBUS_IsBumper(3))
  {
    MOTOR_SetSpeed(0, 0.5);
    MOTOR_SetSpeed(1, 0.5);
    delay(4000);
    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);
  }
  if (ROBUS_IsBumper(0))
  {
    MOTOR_SetSpeed(1, 0.5);
    delay(1000);
    MOTOR_SetSpeed(1, 0);
  }
  if (ROBUS_IsBumper(1))
  {
    MOTOR_SetSpeed(0, 0.5);
    delay(1000);
    MOTOR_SetSpeed(0, 0);
  }
  
}



