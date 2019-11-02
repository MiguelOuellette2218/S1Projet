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
void AdjustSpeed(int gauche,int gaucheDistance, int droit, int droitDistance, float* pSpeed, float speed);
void TurnNoMoving(float speed, float huitTour, bool direction);
/*
*   END Fonctions Simon
*/


/*
*   Suiveur de ligne 
*/
int IdentifierPossibilite(float);
void DecisionDirection(int);