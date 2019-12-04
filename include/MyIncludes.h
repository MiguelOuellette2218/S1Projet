#include <Arduino.h>
#include <LibRobus.h>
#include <math.h>
#include <stdio.h >
#include <string.h>

#include "megalovania.h"


enum COULEUR {ROUGE, VERT, BLEU , JAUNE};
static int modeDeplacement =0;
/*
*   Fonction Gab
*/
int32_t nbrPulses(float cm);
int32_t setSetpoint(float cm, float cycle, float time);

// Note: refaire c'est fonction de manière plus intéligente, (redondance)
void avancerCm(float distance, float time, bool (*)(void));
void reculerCm(float distance, float time, bool (*)(void));
void avancerMoteurCm(int motor, float distance, float time);
void tournerSurUneRoue(int motor, int angle, float time);

// Temp
void moteurInverse(int motor, float distance, float time);
void tournerSurLuiMeme(int motor, int angle, float time);

float corrige_vitesse(int motor, int32_t vitesse_cible);
int32_t ralentir(int32_t vitesse, int32_t distance_presente, int32_t distance_finale, int pourcentage);

float arc(float rayon, float angle);

/*
*   END Fonction Gab
*/

/*
*   Fonctions Simon
*/
float MoveForward(float cm, float* speed, bool (*callback)(void));
void PID(int erreurVitesse, int erreurPosition, float* pSpeed, float speed);
void Turn(float speed, float huitTour, bool direction);
void AdjustSpeed(int gauche,int gaucheDistance, int droit, int droitDistance, float* pSpeed, float speed);
void TurnNoMoving(float speed, float huitTour, bool direction);
void Turn(float* speed, float huitTour, bool direction);
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
*   Parcours du combattant
*/
void FaireParcoursA(COULEUR couleur);
void FaireParcoursB(COULEUR couleur);

/*
*   Pinces
*/
void setupPinces();
void fermerPinces();
void ouvrirPinces();
void setupGate();
void fermerGate();
void ouvrirGate();

//  fonction bluetooth
static char tableau[50] = {0};
int Bluetooth();
void BluetoothRead(char* Tableau);
int ScanBluetooth();
void LireBluetooth();
int IsPaired();

//fonction de suiveur de mur
int comparateurIR();
void mouvementIR ();
int PersonneDevant();
//void mvmt_sonar();
float ConvertBitToDist(float input);
#define distancePersonne 30 //Nous pouvons essaie de diminuer cette distance
void MouvementDetection();
void SetupSonar();

//Fonction de RFID
boolean compareTag(char one[], char two[]);
void RFIDCheck();
int TransformerCodeRFID(char tag[]);
void SonLED(int nbBuzz);
void clearTag(char one[]);
void resetReader();
void setupRFID();
void AppelRFID();

//Fonction pour presentation finale
static int emplacement =0;
static int directionRobot =0;
static int modePieton = 1;
static float tableauEmplacement[25] = {
    25.4,
    57.15,
    57.15,
    25.4, 
    /*Tourner à gauche*/1,
    50.8 ,
    50.8,
    /*Tourner à gauche*/1,
    25.4,
    57.15,
    57.15,
    25.4,
    /*Tourner à droite*/2,
     50.8 ,
     50.8,
     /*Tourner à droite*/2,
    25.45,
    7.15,
    57.15,
    25.4};
void ParcourirBloc(int distance);
void ParcourirProchainBloc(int direction);
void ModePanique();
void ModeBluetooth();
void ModeAutomatisee();
