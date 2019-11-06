#include <Arduino.h>
#include <LibRobus.h>

#include <math.h>

/*
*   Fonction Gab
*/
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

/*
*   END Fonction Gab
*/

/*
*   Fonctions Simon
*/
void MoveFoward(float cm, float* speed, bool (*callback)(void));
void PID(int erreurVitesse, int erreurPosition, float* pSpeed, float speed);

void AdjustSpeed(int gauche,int gaucheDistance, int droit, int droitDistance, float* pSpeed, float speed);
void TurnNoMoving(float speed, float huitTour, bool direction);
#define K 0.0001
#define CIRCONFERENCE 23.94
#define PULSEPARTOUR 3200
#define UnHuit 7.5
/*
*   END Fonctions Simon
*/


/*
*   Suiveur de ligne 
*/
int IdentifierPossibilite(float);
bool DecisionDirection();
bool detectionLigne();
void ScannerPourBalle();
/*
*   END Fonctions Mig
*/


/*
*   Pinces
*/

void setupPinces();
void fermerPinces();
void ouvrirPinces();