#include <Arduino.h>
#include <LibRobus.h>

int32_t nbrPulses(float cm);
int32_t setSetpoint(float cm, float cycle, float speed);
void avancerCm(float distance);
float corrige_vitesse(int motor, int32_t vitesse_cible);
int32_t ralentir(int32_t vitesse, int32_t distance_presente, int32_t distance_finale, int pourcentage);
