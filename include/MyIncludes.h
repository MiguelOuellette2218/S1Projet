#include <Arduino.h>
#include <LibRobus.h>
#define CIRCONFERENCE 23.94 //23,94 selon le wiki de LibRobus
// Nombre de pulse des encodeur par tour de roue
#define PULSEPARTOUR 3200
//#define UnHuit 116.87
#define UnHuit 7.5
// Valeur des moteurs
void CmMove(float , float* );
void AdjustSpeed(int , int , float*, float);
void TurnNoMoving(float , float, bool);
void test(void);
