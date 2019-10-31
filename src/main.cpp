#include"MyIncludes.h"

#define CIRCONFERENCE 24.25

//sint mainbumper();

vector gauche;
vector droite;

//int32_t gauche[1000] = {0};
//int32_t droite[1000] = {0};

void setup() {
  // put your setup code here, to run once:

  BoardInit();

/*
  Serial.begin(9600);  
  cheatinit(&gauche, &droite);

  for(sl i=0; i<10; i++){
    Serial.println("################");
    push(&gauche, i);
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(gauche.size);

    for (ul j = 0; j < gauche.size; j++)
    {
      Serial.println(gauche.data[j]);
    }
    Serial.println("################");
  }

  delay(1500);
  */
}

void loop() {

float yolo =analogRead(A0)*(5.0 / 1023.0); 
Serial.println(yolo);

//print

//float speed [2] = {0.5,0.5};
  //MoveFoward(200,speed);
  //Serial.println("bla");
  //cheatProc(gauche , droite);
  //delay(200);

  //cheatCodeProc(&gauche, &droite);
  //delay(200);
  
  /*
  avancerCm(112, 3.5);
  tournerSurUneRoue(LEFT, 90, 2);
  avancerCm(73, 3.5);
  tournerSurUneRoue(RIGHT, 90, 2);
  avancerCm(85, 3.5);
  tournerSurUneRoue(RIGHT, 45, 2);
  avancerCm(156, 7);
  tournerSurUneRoue(LEFT, 90, 2);
  avancerCm(50, 3.5);
  tournerSurUneRoue(RIGHT, 45, 2);
  avancerCm(100, 3.5);

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
  */
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
}
