#include "MyIncludes.h"
int RFIDResetPin = 13;
#define PIN 2

void setupRFID()
{
  Serial3.begin(115200);
  pinMode(RFIDResetPin, OUTPUT);
  digitalWrite(RFIDResetPin, HIGH);
  pinMode(PIN, OUTPUT);
}

void AppelRFID()
{
 //Serial.println(Serial2.read());
  char tagString[13]; //les cartes RFID utilise 12 charactère au total
  int index = 0;
  boolean reading = false;
  while(Serial3.available()){

    int readByte = Serial3.read();

    //TODO : Briser la condition si il n'y a rien , pour sauver de la ressource et du temps
    if(readByte == 2) reading = true; //begining of tag
    if(readByte == 3) reading = false; //end of tag

    if(reading && readByte != 2 && readByte != 10 && readByte != 12){
      //store the tag
      tagString[index] = readByte;
      index ++;
    }
  }

  if(strlen(tagString) == 0);
  else 
  {
    int rep = TransformerCodeRFID(tagString);
    //Serial.println(tagString);
    //Serial.println(TransformerCodeRFID(tagString));
    SonLED(PIN,rep);
    Serial3.print((short)rep, HEX);
  }
  
  clearTag(tagString);
  clearTag(tagString);
  resetReader();  

}

//Reset le lecteur RFID pour relir une autre carte
void resetReader()
{
  digitalWrite(RFIDResetPin, LOW);
  digitalWrite(RFIDResetPin, HIGH);
  delay(1000);
}

//reset la chaine de charactere -tagString- pour écrire un autre carte
void clearTag(char one[])
{
  for(int i = 0; i < strlen(one); i++){
    one[i] = 0;
  }
}
//active la led et le son en sortant le voltage
//de la pin X et en faisant X nbBuzz au buzzer
void SonLED(int pin,int nbBuzz)
{
  if(nbBuzz == -1)
  {
    for(int i = 0; i < 50; i++)
    {
     digitalWrite(pin, HIGH);
     delay(10);
     digitalWrite(pin, LOW);
     delay(10);
    }
  }
  else{
  for(int j = 0; j < nbBuzz; j++)
  {
    for(int i = 0; i < 10; i++)
    {
     digitalWrite(pin, HIGH);
     delay(10);
     digitalWrite(pin, LOW);
     delay(10);
    }
    delay(100);
  }
  }
}
/*transforme la chaine de charactère donné par 
 * le RFID en un simple nombre pour l'envoyer à 
 * l'écran OLED de ma boi simon. il utilise la
 * fonction <compareTag> pour comparer le tag
 * du RFID et des tag hardcodé pour donner un
 * nombre hardcodé.
*/
int TransformerCodeRFID(char tag[])
{
  char tag1[13] = "0F027D729391";
  char tag2[13] = "0F027D605040";
  char tag3[13] = "0F027D729290";

  if (compareTag(tag, tag1)) return 1;
  else if (compareTag(tag, tag2)) return 2;
  else if (compareTag(tag, tag3)) return 3;
  else return -1;
}


/*(fonction trouvé sur internet) compare 2 tag,
 * le premier est le tag donné par le scanneur RFID et le 2e
 * hardcodé dans la fonction <TransformerCodeRFID> pour les
 * comparer. c'est pour faire un strcmp mais il ne fonctionnait
 * pas tous le temps
*/
boolean compareTag(char one[], char two[])
{
  if(strlen(one) == 0) return false; //empty

    for(int i = 0; i < 12; i++)
    {
      if(one[i] != two[i]) return false;
    }

  return true;
}