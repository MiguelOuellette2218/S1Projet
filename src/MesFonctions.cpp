
#include "MyIncludes.h"

#define CIRCONFERENCE 24.25 //23,94 selon le wiki de LibRobus
#define PULSEPARTOUR 3200   // Nombre de pulse des encodeur par tour de roue
#define DISTANCEROUE 18.8
#define DELAY 20 // en ms
//#define KP 0.0003 // 20B
#define KP 0.00065  // 20A
#define KI 0.000009 // 20A

enum COULEUR {ROUGE, VERT, BLEU , JAUNE};

/*
    * Fonction qui permet de faire avancer le robot en fonction d'une distance
    * float distance : distance en cm
    */
void avancerCm(float distance, float time)
{
    int32_t pulse_distance = nbrPulses(distance);
    int32_t nbr_pulse = 0;
    int32_t vitesse_cible = setSetpoint(distance, DELAY, time);

    float pwmL = 0;
    float pwmR = 0.04;

    while (nbr_pulse < pulse_distance)
    {
        ENCODER_Reset(LEFT);
        ENCODER_Reset(RIGHT);

        //vitesse_cible = ralentir(vitesse_cible, nbr_pulse, pulse_distance, 20);

        // Debug
        Serial.print(pwmL);
        Serial.print("   -   ");
        Serial.println(pwmR);

        // Définition de la vitesse
        MOTOR_SetSpeed(LEFT, pwmL);
        MOTOR_SetSpeed(RIGHT, pwmR);

        delay(DELAY);

        // Correction de la vitesse
        pwmL += corrige_vitesse(LEFT, vitesse_cible);
        pwmR += corrige_vitesse(RIGHT, vitesse_cible);

        nbr_pulse += ENCODER_Read(LEFT);
    }

    // Arrêt des moteurs
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
}

/*
    * Fonction qui fait avancer un motor seul
    * int motor : id du moteur
    * int32_t distance : distance en cm
    */
void avancerMoteurCm(int motor, float distance, float time)
{
    int32_t pulse_distance = nbrPulses(distance);
    int32_t nbr_pulses = 0;
    int32_t vitesse_cible = setSetpoint(distance, DELAY, time);

    float pwm = 0;

    while (nbr_pulses < pulse_distance)
    {
        ENCODER_Reset(motor);

        MOTOR_SetSpeed(motor, pwm);

        delay(DELAY);

        pwm += corrige_vitesse(motor, vitesse_cible);

        nbr_pulses += ENCODER_Read(motor);
    }

    MOTOR_SetSpeed(motor, 0);
}

/*
    * Fonction qui fait tourner les deux moteur à sens inverse
    * float distance : distance sur lequel faire tourner le moteur
    * float time : temps pour l'opération
    */
void moteurInverse(float distance, float time)
{
    int32_t pulse_distance = nbrPulses(distance);
    int32_t nbr_pulse = 0;
    int32_t vitesse_cible = setSetpoint(distance, DELAY, time);

    float pwmL = 0;
    float pwmR = 0.04;

    while (nbr_pulse < pulse_distance)
    {
        ENCODER_Reset(LEFT);
        ENCODER_Reset(RIGHT);

        //vitesse_cible = ralentir(vitesse_cible, nbr_pulse, pulse_distance, 20);

        // Debug
        Serial.print(pwmL);
        Serial.print("   -   ");
        Serial.println(pwmR);

        // Définition de la vitesse
        MOTOR_SetSpeed(LEFT, pwmL);
        MOTOR_SetSpeed(RIGHT, pwmR);

        delay(DELAY);

        // Correction de la vitesse
        pwmL += corrige_vitesse(LEFT, vitesse_cible);
        pwmR += corrige_vitesse(RIGHT, -vitesse_cible);

        nbr_pulse += ENCODER_Read(LEFT);
    }

    // Arrêt des moteurs
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
}

/*
    * Fonction qui fait tourner le robot sur une roue
    * int motor : sens dans lequel on veut tourner
    * int angle : angle en degrés vers lequel s'orienter
    */
void tournerSurUneRoue(int motor, int angle, float time)
{
    // Inversion des moteurs
    if (motor == LEFT)
    {
        motor = RIGHT;
    }
    else
    {
        motor = LEFT;
    }

    float distance = 1;
    distance += arc(DISTANCEROUE, angle);

    avancerMoteurCm(motor, distance, time);
}

/*
    * Fonctione qui fait tourner le robot sur lui même
    * int angle : angle den degrés vers lequel s'orienter
    * int time : temps pour tourner
    */
void tournerSurLuiMeme(int angle, float time)
{
    float distance = arc(DISTANCEROUE / 2, angle);

    moteurInverse(distance, time);
}

/*
    * Fonction qui calcul l'arc d'un cercle en fonction d'un angle et d'un rayon donnée
    * float rayon : rayon en cm
    * float angle : angle en degrés
    * return : distance en cm
    */
float arc(float rayon, float angle)
{
    return (2 * PI * rayon * angle) / 360;
}

/*
    * Corrige la vitesse
    * int motor : moteurs à corriger
    * int32_t vitesse en pulse par seconde
    */
float corrige_vitesse(int motor, int32_t vitesse_cible)
{
    static float erreurAcc[2] = {0};

    float erreur = vitesse_cible - ENCODER_Read(motor);

    if (erreur == 0)
    {
        erreurAcc[motor] = 0;
    }

    erreurAcc[motor] += erreur;

    float correction = (erreur * KP) + (erreurAcc[motor] * KI);

    return correction;
}

/*
    * Fonction qui défini le nombre de pulse nécésaire pour une distance
    * float cm : distance en cm
    */
int32_t nbrPulses(float cm)
{
    return (cm * PULSEPARTOUR) / CIRCONFERENCE;
}

/*
    * Fonction qui défini le setpoint (Nombre de pulse théorique par cycle)
    * float cm : distance en cm
    * float cycle : temps d'un cycle en ms
    */
int32_t setSetpoint(float cm, float cycle, float time)
{
    int32_t pulses = nbrPulses(cm);
    return pulses * (cycle / 1000) / time;
}

/*
    * Fonction qui ralenti le robot en fonction de ça vitesse
    * int32_t vitesse : vitesse en pulse par cycle (DELAY)
    * int32_t distance_presente : distance parcourus
    * int32_t distance_finale : distance à atteindre
    * int pourcentage : pourcentage de réduction de la vitesse
    */
int32_t ralentir(int32_t vitesse, int32_t distance_presente, int32_t distance_finale, int pourcentage)
{
    if (distance_presente >= distance_finale - 2 * PULSEPARTOUR)
    {
        Serial.println("Ralenti!!!");
        return vitesse - (vitesse * (pourcentage / 100));
    }
    else
    {
        return vitesse;
    }
}

void ScannerPourBalle()
{
    // tournerSurLuiMeme(-90, 1);
        // tourner a 45 degrée
         float pSpeed [2] = {50,50};
    TurnNoMoving(.5, 1,0);

    //TurnNoMoving()

    int incrementAngle = 36;

    //float distanceCapteur = (5000/ ROBUS_ReadIR(2)+ 5);

    float distanceCapteur = (-0.0943*ROBUS_ReadIR(1)) + (float)56.5 - 10;
    float AnciennedistanceCapteur = distanceCapteur;

    float difference = 30;

    float anglePetit = (float)180/incrementAngle;

    anglePetit = anglePetit/(float)45;

                MOTOR_SetSpeed(LEFT, 0.3);
                MOTOR_SetSpeed(RIGHT, -0.3);
    for (size_t i = 0; i < (incrementAngle/4)*3; i++)
    {
        //Attribue l'ancienne valeur de distance à une variable puis change la valeur de la distance du présent
        //AnciennedistanceCapteur = distanceCapteur;
        distanceCapteur = (-0.0943*ROBUS_ReadIR(1)) + (float)56.5 - 10;
       
            //Trouve si l'ancienne distance par rapport a la nouvelle est trop differente (donc qu'il y a probablement un object devant lui)
            if (distanceCapteur <difference )
            {
                //MoveFoward(distanceCapteur,50 ,false);
                 MOTOR_SetSpeed(LEFT, 0);
                MOTOR_SetSpeed(RIGHT, 0);
                delay(200);
                //TurnNoMoving(.5, anglePetit*2, 1);
                //delay(200);
                //avancerCm(distanceCapteur + 5, 0.5);
                
                MoveFoward(distanceCapteur,pSpeed ,0);

                
                
                break;
            }
            else
            {
                //tournerSurLuiMeme((int)10,(float)200);
                //TurnNoMoving(.5, anglePetit, 1);
            }
        
        delay(100);
    }
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
}

void fermerPinces()
{
    SERVO_SetAngle(0, 90);
}

void ouvrirPinces()
{
    SERVO_SetAngle(0, 135);
}
void setupPinces()
{
    SERVO_Enable(0);
    delay(200);
    ouvrirPinces();
}

void fermerGate()
{
    SERVO_SetAngle(1, 90);
}

void ouvrirGate()
{
    SERVO_SetAngle(1, 0);
}
void setupGate()
{
    SERVO_Enable(1);
    delay(200);
    ouvrirGate();
}



void FaireParcoursA(COULEUR couleur)
{
if(couleur == ROUGE)
{
//Tourne a gauche pour être en angle de 45 par rapport au but vert
avancerCm(100 , 2);
tournerSurLuiMeme(90 ,1);
}
if(couleur == VERT)
{
    //Tourne a gauche pour être en angle de 45 par rapport au but rouge
avancerCm(100 , 2);
tournerSurLuiMeme(-90 ,1);
}
if(couleur == BLEU)
{
//Tourne a droit pour être en angle de 45 par rapport au but bleu
tournerSurLuiMeme(90 ,1);
}
if(couleur == JAUNE)
{
//Tourne a gauche pour être en angle de 45 par rapport au but jaune
tournerSurLuiMeme(90 ,1);
}

//Avancer jusqu'a trouver un ligne blanche
DecisionDirection();
ScannerPourBalle();
fermerPinces();

//Reculer pour revenir vers la ligne
avancerCm(-100,2);
tournerSurLuiMeme(180,1);
DecisionDirection();

//Dropper la balle dans le centre
ouvrirPinces();

//DECALISSÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉÉ
avancerCm(-200,5);
delay(1000000000);
}


void FaireParcoursB( COULEUR couleur )
{
    //Attendre le temps que le premier robot fasse sa job
delay(1000*60);

//Scan pour la balle
ScannerPourBalle();

//PArt a course pour le yeet dans un but
//BallonChasseur(couleur);
}
