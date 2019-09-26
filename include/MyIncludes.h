#include <Arduino.h>
#include <LibRobus.h>
#define CIRCONFERENCE 24.25 //23,94 selon le wiki de LibRobus
// Nombre de pulse des encodeur par tour de roue
#define PULSEPARTOUR 3200
// Valeur des moteurs
void CmMove(float , float );
void AdjustSpeed(int , int , float*);

