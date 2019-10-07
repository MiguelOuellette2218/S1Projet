
#include"MyIncludes.h"

#define CIRCONFERENCE 24.25 //23,94 selon le wiki de LibRobus
#define PULSEPARTOUR 3200 // Nombre de pulse des encodeur par tour de roue
#define DELAY 20 // en ms
#define KP 0.0003
#define KI 0.000002

/*
* Fonction qui permet de faire avancer le robot en fonction d'une distance
* float distance : distance en cm
*/
void avancerCm(float distance)
{
    int32_t pulse_distance = nbrPulses(distance);
    int32_t nbr_pulse = 0;
    int32_t vitesse_cible = setSetpoint(distance, DELAY, 0.2);

    float pwmL = 0;
    float pwmR = 0;

    while(nbr_pulse < pulse_distance)
    {
        ENCODER_Reset(LEFT);
        ENCODER_Reset(RIGHT);

        vitesse_cible = ralentir(vitesse_cible, nbr_pulse, pulse_distance, 20);

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
* Corrige la vitesse
* int motor : moteurs à corriger
* int32_t vitesse en pulse par seconde
*/
float corrige_vitesse(int motor, int32_t vitesse_cible)
{
    static float erreurAcc[2] = {0};

    float erreur =  vitesse_cible - ENCODER_Read(motor);

    if(erreur == 0){
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
* float speed : vitesse en m/s, ne peut pas aller plus haut que 1 ou -1 m/s
*/
int32_t setSetpoint(float cm, float cycle, float speed)
{
    if(speed > 1 && speed < 1) // Limite de vitesse de 1 m/s
    {
        return -1;
    }

    int32_t pulses = nbrPulses(cm);
    return (pulses * (cycle / 1000)) / (1 / speed);
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
    if(distance_presente >= distance_finale - 2*PULSEPARTOUR)
    {
        Serial.println("Ralenti!!!");
        return vitesse - (vitesse * (pourcentage / 100));
    } else
    {
        return vitesse;
    }
}

