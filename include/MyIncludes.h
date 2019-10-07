#include <Arduino.h>
#include <LibRobus.h>

#include <math.h>

int32_t nbrPulses(float cm);
int32_t setSetpoint(float cm, float cycle, float speed);

void avancerCm(float distance);
void avancerMoteurCm(int motor, float distance);
void tournerSurUneRoue(int motor, int angle);

float corrige_vitesse(int motor, int32_t vitesse_cible);
int32_t ralentir(int32_t vitesse, int32_t distance_presente, int32_t distance_finale, int pourcentage);

float arc(float rayon, float angle);

void AdjustSpeed(int gauche,int gaucheDistance, int droit, int droitDistance, float* pSpeed, float speed);
void TurnNoMoving(float speed, float huitTour, bool direction);