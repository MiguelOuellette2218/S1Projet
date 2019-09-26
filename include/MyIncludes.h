#include <Arduino.h>
#include <LibRobus.h>
#define CIRCONFERENCE 24.25 //23,94 selon le wiki de LibRobus
// Nombre de pulse des encodeur par tour de roue
#define PULSEPARTOUR 3200
// Valeur des moteurs
#define GAUCHE 0
#define DROIT 1
#define PIN13 13
void CmMove(float , float );

