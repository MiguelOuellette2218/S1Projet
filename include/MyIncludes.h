#include <Arduino.h>
#include <LibRobus.h>

int32_t nbrPulses(float cm);
int32_t setSetpoint(float cm, float cycle, float speed);
void avancerCm(float distance);
float corrige_vitesse(int motor, int32_t vitesse_cible);

