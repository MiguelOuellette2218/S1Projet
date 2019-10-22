#include <Arduino.h>
#include <LibRobus.h>

#include <math.h>

#include "vector.h"

int32_t nbrPulses(float cm);
int32_t setSetpoint(float cm, float cycle, float time);

// Note: refaire c'est fonction de manière plus intéligente, (redondance)
void avancerCm(float distance, float time);
void avancerMoteurCm(int motor, float distance, float time);
void tournerSurUneRoue(int motor, int angle, float time);

// Temp
void moteurInverse(float distance, float time);
void tournerSurLuiMeme(int angle, float time);

float corrige_vitesse(int motor, int32_t vitesse_cible);
int32_t ralentir(int32_t vitesse, int32_t distance_presente, int32_t distance_finale, int pourcentage);

float arc(float rayon, float angle);

void AdjustSpeed(int gauche,int gaucheDistance, int droit, int droitDistance, float* pSpeed, float speed);
void TurnNoMoving(float speed, float huitTour, bool direction);

/**
 * 
 * CHEATCODE
 * 
**/

int bumper();
void cheatinit(vector* gauche, vector *droite);
void cheatCodeProc(vector* gauche, vector *droite);

void push(vector* p, ul x);

//cheatcode 2
void cheatProc(int32_t* gauche, int32_t* droite);