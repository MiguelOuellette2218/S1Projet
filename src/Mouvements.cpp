#include "MyIncludes.h"
#define ROBOTA 0.035
#define ROBOTB 0
#define USEROBOT ROBOTA
#define CIRCONFERENCE 23.94
#define PULSEPARTOUR 3200
#define UnHuit 7.5
#define DISTANCEROUE 18.8
#define DELAY 20 // en ms
//#define KP 0.0003 // 20B
#define KP 0.00065  // 20A
#define KI 0.000009 // 20B

/*
* Fonction pour avancer
* float cm: Distance à parcourir
* float* speed: vitesse voulue
* bool (*callback)(void): fonction d'intéruption de la méthode
*/
float MoveForward(float cm, float *speed, bool (*callback)(void))
{
   // Serial.println("DEBUG// MODE MOVEFORWARD \\\\DEBUG");
   // Serial.println("Distance à parcourir"); 
   //Serial.println(cm);   

    //delay(200);
    int32_t pulseDistance = (cm * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    //Init des variables
    unsigned long long time = 0;
    unsigned long long oldTime = 0;
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed[2] = {0, 0}; //pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit
    float speedG = 0.1;       //Partir lentement
    float speedD = 0.1;
    float ralentissement = 0;

    while ((ENCODER_Read(LEFT) < pulseDistance) || (ENCODER_Read(RIGHT) < pulseDistance))
    {
        time = millis();

        //delay(50);
        //Serial.print("Time : ");
        //Serial.print(time);
        //Serial.print(" - ");
        //Serial.println(oldTime);

        if (time - oldTime > 49)
        {
           // Serial.println("If milli"); 
            if(PersonneDevant() == 1 && modePieton==1)
            {
             //   Serial.println("Arreter pendant le mouvement"); 
                  
                MOTOR_SetSpeed(LEFT, 0);
                MOTOR_SetSpeed(RIGHT, 0); 


                float retourDistance = (ENCODER_Read(LEFT)*CIRCONFERENCE)/PULSEPARTOUR;
              // float retourDistance = ENCODER_Read(LEFT);
                return retourDistance;
            }       
            else
            {
                

            if (ENCODER_Read(LEFT) < pulseDistance - PULSEPARTOUR)
            { //Accélération
             //   Serial.println("Acceleration"); 
                if (speedG + 0.05 < speed[0])
                    speedG += 0.05;
                else
                    speedG = speed[0];
                if (speedD + 0.05 < speed[1])
                    speedD += 0.05;
                else
                    speedD = speed[1];
            }
            else
            { //Ralentissement
               // Serial.println("Ralentissement"); 
                if (ralentissement < speedG - 0.30)
                    ralentissement += 0.05 * (speedD + speedG);
            }

            lastLeft = newLeft; //Enregistre les anciennes valeurs avant de relire
            lastRight = newRight;
            newLeft = ENCODER_Read(LEFT);
            newRight = ENCODER_Read(RIGHT);
            //ADJUST AND SET SPEED
            int erreurVitesse = (newLeft - lastLeft) - (newRight - lastRight);
            int erreurPosition = newLeft - newRight;
            PID(erreurVitesse, erreurPosition, pSpeed, speedD);
            MOTOR_SetSpeed(LEFT, speedG + pSpeed[0] - ralentissement);
            MOTOR_SetSpeed(RIGHT, speedD + pSpeed[1] - ralentissement + USEROBOT);
            time = millis();
            oldTime = time;
            //Serial.println("Call de PID"); 
            }
        }
        else
        {
           // Serial.println("if not milli"); 
        }
        
    }
    //TURN TO 0 MOTORS
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    speed[0] = speedG + pSpeed[0];
    speed[1] = speedD + pSpeed[1];

    return cm;
}

void ParcourirBloc(int distance)
{
    //Serial.println("DEBUG// MODE PARCOURIRBLOC \\\\DEBUG");
    float pSpeed[2] = {0.5, 0.5};
    float distanceParcourus = MoveForward(distance, pSpeed, false);
    float distanceRestante = distance - distanceParcourus;
    //Serial.println("feedbackDistance");
    //         Serial.println(feedbackDistance);

    if (modePieton == 1)
    {
        while (distanceRestante > 5)
        {
            if (PersonneDevant() == false)
            {
                pSpeed[0] = 0.5;
                pSpeed[1] = 0.5;
                distanceParcourus = MoveForward(distanceRestante, pSpeed, false);
                   // Serial.println("Distance Parcouru");
                  // Serial.println(distanceParcourus);
                distanceRestante = distanceRestante - distanceParcourus;

                //feedbackDistance = distance -feedbackDistance;
                // Serial.println("distanceRestante");
                // Serial.println(distanceRestante);
            }
            else
            {
                MOTOR_SetSpeed(LEFT, 0);
                MOTOR_SetSpeed(RIGHT, 0);
            }
        }
    }
    
}


/*
* Fonction pour tourner selon un huitieme de tour en avancant
* float speed: tableau de 2 element de vitesse de moteur
* float* huittour: huitieme de 360 degree (ex : 45 degree =1 , 135 =3)
* bool direction : permet de savoir la directifon , 0 = par la gauche et 1 est par la droite
*/
void Turn(float *speed, float huitTour, bool direction)
{
    int pulseDistance = (UnHuit * huitTour * PULSEPARTOUR) / CIRCONFERENCE;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int time = 0;
    int oldTime = 0;
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed[2] = {0, 0}; //pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit
    float speedG, speedD;
    if (direction)
    {
        speedG = speed[0]; //Partir lentement
        speedD = 0 - speed[1];
    }
    else
    {
        speedG = 0 - speed[0]; //Partir lentement
        speedD = speed[1];
    }
    float ralentissement = 0;
    if (direction) //Turn Right
    {
        while ((ENCODER_Read(LEFT) < pulseDistance) && (ENCODER_Read(RIGHT) > (0 - pulseDistance)))
        {
            time = millis();
            if (time - oldTime > 49)
            {
                lastLeft = newLeft;
                lastRight = newRight;
                newLeft = ENCODER_Read(LEFT);
                newRight = ENCODER_Read(RIGHT);
                int erreurVitesse = (abs(newLeft) - abs(lastLeft)) - (abs(newRight) - abs(lastRight));
                int erreurPosition = abs(newLeft) - abs(newRight);
                //Serial.println(erreurVitesse);
                //Serial.println(erreurPosition);
                //Serial.println("_");
                PID(erreurVitesse, erreurPosition, pSpeed, speedD);
                //MOTOR_SetSpeed(LEFT, speed * pSpeed[0]); //- pSpeed[0]);
                //MOTOR_SetSpeed(RIGHT, (0 - speed) * pSpeed[1]);

                MOTOR_SetSpeed(LEFT, speedG - pSpeed[0]);
                MOTOR_SetSpeed(RIGHT, speedD + pSpeed[1] - USEROBOT);
            }
        }
    }
    else
    {
        while ((ENCODER_Read(LEFT) > (0 - pulseDistance)) && (ENCODER_Read(RIGHT) < pulseDistance))
        {
            time = millis();
            if (time - oldTime > 49)
            {
                lastLeft = newLeft;
                lastRight = newRight;
                newLeft = ENCODER_Read(LEFT);
                newRight = ENCODER_Read(RIGHT);
                //ADJUST AND SET SPEED
                int erreurVitesse = (abs(newLeft) - abs(lastLeft)) - (abs(newRight) - abs(lastRight));
                int erreurPosition = abs(newLeft) - abs(newRight);
                //Serial.println(erreurVitesse);
                //Serial.println(erreurPosition);
                //Serial.println("_");
                PID(erreurVitesse, erreurPosition, pSpeed, speedD);
                //MOTOR_SetSpeed(LEFT, (0 - speed) * pSpeed[0]); //- pSpeed[0]);
                //MOTOR_SetSpeed(RIGHT, speed * pSpeed[1]);
                MOTOR_SetSpeed(LEFT, speedG - pSpeed[0]);
                MOTOR_SetSpeed(RIGHT, speedD + pSpeed[1] - USEROBOT);
            }
        }
    }

    MOTOR_SetSpeed(RIGHT, 0);
    MOTOR_SetSpeed(LEFT, 0);
    speed[0] = speedG + pSpeed[0];
    speed[1] = speedD + pSpeed[1];
}

/*
* Fonction pour corriger la vitesse, utiliser avec d'autre fonction (donc ne pas utiliser seul)
*/
void PID(int erreurVitesse, int erreurPosition, float *pSpeed, float speed)
{
    static int oldErreurVitesse = 0;
    //Serial.print("Erreur de vitesse ");
    //Serial.println(erreurVitesse);
    //Serial.print("Erreur de position ");
    //Serial.println(erreurPosition);
    //Serial.print("SG ");
    //Serial.println(pSpeed[0],4);
    //Serial.print("SD ");
    //Serial.println(pSpeed[1],4);

    //Droit plus loin que gauche
    if (erreurPosition < 0) //            D>G
    {
        if (erreurVitesse > 0) //         #G>D#
        {                      //GOOD, en train de corrigé
            int x = 2;
            if (abs(erreurPosition) > abs(erreurVitesse))
                x = 0.5;
            pSpeed[1] -= (x * K * (abs(erreurPosition) - abs(erreurVitesse)));
            pSpeed[0] += (x * K * (abs(erreurPosition) - abs(erreurVitesse)));
        }
        else //Pas good, doit corrigé
        {
            //Dans ce cas, il faut corrigé l'erreur de position et donc mettre une erreur dans la vitesse
            pSpeed[1] -= (K * abs(erreurPosition) + K * abs(erreurVitesse));
            pSpeed[0] += (K * abs(erreurPosition) + K * abs(erreurVitesse));
            // Serial.println("D>Gcorrige");
        }
    }

    //Gauche plus loin que droit
    else if (erreurPosition > 0) //   G>D
    {
        if (erreurVitesse < 0) //     #D>G#
        {                      //GOOD
            int x = 2;
            if (abs(erreurPosition) > abs(erreurVitesse))
                x = 0.5;
            pSpeed[0] -= (x * K * (abs(erreurPosition) - abs(erreurVitesse)));
            pSpeed[1] += (x * K * (abs(erreurPosition) - abs(erreurVitesse)));
        }
        else //pas good
        {
            //Dans ce cas, il faut corrigé l'erreur de position et donc mettre une erreur dans la vitesse
            pSpeed[0] -= (K * abs(erreurPosition) + K * abs(erreurVitesse));
            pSpeed[1] += (K * abs(erreurPosition) + K * abs(erreurVitesse));
            // Serial.println("G>Dcorrige");
        }
    }
    oldErreurVitesse = erreurVitesse;
    //Serial.println(".");
}

/*
* Fonction pour tourner selon un huitieme de tour sans avancer
* float speed: tableau de 2 element de vitesse de moteur
* float* huittour: huitieme de 360 degree (ex : 45 degree =1 , 135 =3)
* bool direction : permet de savoir la direction , 0 = par la gauche et 1 est par la droite
*/
void TurnNoMoving(float speed, float huitTour, bool direction)
{
  //  Serial.println("DEBUG // TURNNOMOVING \\\\ DEBUG");
    int pulseDistance = ((UnHuit * huitTour * PULSEPARTOUR) / CIRCONFERENCE) + 5;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    unsigned long long time = 0;
    unsigned long long oldTime = 0;
    int lastLeft = 0;
    int lastRight = 0;
    int newLeft = 0;
    int newRight = 0;
    float pSpeed[2] = {1, 1}; //pSpeed[0]=Speed Gauche //pSpeed[1]=Speed Droit

  //  Serial.println(direction); // DEBUG

    if (direction)            //Turn Right
    {
        while ((ENCODER_Read(LEFT) < pulseDistance) && (ENCODER_Read(RIGHT) > (0 - pulseDistance)))
        {
            time = millis();
          //  Serial.print((float)newLeft);
          //  Serial.print("-");
         //   Serial.println((float)lastLeft);     
          
            if (time - oldTime > 20)
            {

                lastLeft = newLeft;
                lastRight = newRight;
                newLeft = ENCODER_Read(LEFT);
                newRight = ENCODER_Read(RIGHT);
                AdjustSpeed(newLeft - lastLeft, 0, 0 - (newRight - lastRight), 0, pSpeed, speed);
                MOTOR_SetSpeed(LEFT, speed * pSpeed[0]); //- pSpeed[0]);
                MOTOR_SetSpeed(RIGHT, (0 - speed) * pSpeed[1]);
            }
        }
        newLeft = ENCODER_Read(LEFT);
        newRight = ENCODER_Read(RIGHT);
        if (newLeft < pulseDistance)
        {
            MOTOR_SetSpeed(RIGHT, 0);
            while (newLeft < pulseDistance)
            {
                newLeft = ENCODER_Read(LEFT);
            }
            MOTOR_SetSpeed(LEFT, 0);
        }
        else if (newRight < (0 - pulseDistance))
        {
            MOTOR_SetSpeed(LEFT, 0);
            while (newRight < (0 - pulseDistance))
            {
                newRight = ENCODER_Read(RIGHT);
            }
            MOTOR_SetSpeed(RIGHT, 0);
        }
    }
    else
    {
        while ((ENCODER_Read(LEFT) > (0 - pulseDistance)) && (ENCODER_Read(RIGHT) < pulseDistance))
        {
            time = millis();
            if (time - oldTime > 20)
            {
                lastLeft = newLeft;
                lastRight = newRight;
                newLeft = ENCODER_Read(LEFT);
                newRight = ENCODER_Read(RIGHT);
                AdjustSpeed(0 - (newLeft - lastLeft), 0, newRight - lastRight, 0, pSpeed, speed);
                MOTOR_SetSpeed(LEFT, (0 - speed) * pSpeed[0]); //- pSpeed[0]);
                MOTOR_SetSpeed(RIGHT, speed * pSpeed[1]);
            }
        }
        newLeft = ENCODER_Read(LEFT);
        newRight = ENCODER_Read(RIGHT);
        if (newLeft > (0 - pulseDistance))
        {
            MOTOR_SetSpeed(RIGHT, 0);
            while (newLeft > (0 - pulseDistance))
            {
                newLeft = ENCODER_Read(LEFT);
            }
            MOTOR_SetSpeed(LEFT, 0);
        }
        else if (newRight < pulseDistance)
        {
            MOTOR_SetSpeed(LEFT, 0);
            while (newRight < pulseDistance)
            {
                newRight = ENCODER_Read(RIGHT);
            }
            MOTOR_SetSpeed(RIGHT, 0);
        }
    }

    MOTOR_SetSpeed(RIGHT, 0);
    MOTOR_SetSpeed(LEFT, 0);
}

/*
* Fonction qui permet d'ajuster la vitesse des moteurs pour le pid , NE PAS UTILISER SEUL
*/
void AdjustSpeed(int gauche, int gaucheDistance, int droit, int droitDistance, float *pSpeed, float speed)
{
    if (gauche > droit) //Grosse ajustement          Gauche trop rapide
    {
        int erreur = gauche - droit;
        if (pSpeed[1] < 1)
            pSpeed[1] += (0.0001 * erreur);
        else
            pSpeed[0] -= (0.0001 * erreur);
        // Serial.println("Erreur G > D");
        // Serial.println(erreur);
    }
    else if (droit > gauche) //Grosse ajustement    Droit trop rapide
    {
        int erreur = droit - gauche;
        if (pSpeed[1] < 1)
            pSpeed[1] += (0.0001 * erreur);
        else
            pSpeed[1] -= (0.0001 * erreur);
        //  Serial.println("Erreur D > G");
        //  Serial.println(erreur);
    }
}

/*
* Fonction qui permet de faire avancer le robot en fonction d'une distance
* float distance : distance en cm
* float time : temps pour parcourir la distance
* bool (*)(void) : fonction pointeur pour stopper l'action
*/
void avancerCm(float distance, float time, bool (*callback)())
{
     Serial.println("Distance à parcourir");
        Serial.println(distance);
   
    int32_t pulse_distance = nbrPulses(distance);
    int32_t nbr_pulse = 0;
    int32_t vitesse_cible = setSetpoint(distance, DELAY, time);

    float pwmL = 0;
    float pwmR = 0.04;

    while (nbr_pulse < pulse_distance)
    {
        if (callback)
            if (callback())
                break;

        ENCODER_Reset(LEFT);
        ENCODER_Reset(RIGHT);

        //vitesse_cible = ralentir(vitesse_cible, nbr_pulse, pulse_distance, 20);

        // Debug
        //Serial.print(pwmL);
        //Serial.print("   -   ");
        //Serial.println(pwmR);

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
* Fonction qui permet de reculer le robot
* float distance: distance a parcourir
* float time: temps en combien de temps il faut parcourir la distance
*/
void reculerCm(float distance, float time, bool (*callback)())
{
    int32_t pulse_distance = -1 * nbrPulses(distance);
    int32_t nbr_pulse = 0;
    int32_t vitesse_cible = -1 * setSetpoint(distance, DELAY, time);

    float pwmL = 0;
    float pwmR = 0.04;

    while (nbr_pulse > pulse_distance)
    {
        if (callback)
            if (callback())
                break;

        ENCODER_Reset(LEFT);
        ENCODER_Reset(RIGHT);

        //vitesse_cible = ralentir(vitesse_cible, nbr_pulse, pulse_distance, 20);

        // Debug
        //Serial.print(pwmL);
        //Serial.print("   -   ");
        //Serial.println(pwmR);
        //Serial.println(nbr_pulse);

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
    * int motor: Sens de rotation
    * float distance : distance sur lequel faire tourner le moteur
    * float time : temps pour l'opération
    */
void moteurInverse(int motor, float distance, float time)
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
        //Serial.print(pwmL);
        //Serial.print("   -   ");
        //Serial.println(pwmR);

        // Définition de la vitesse
        MOTOR_SetSpeed(LEFT, pwmL);
        MOTOR_SetSpeed(RIGHT, pwmR);

        delay(DELAY);

        // Correction de la vitesse
        if (motor == RIGHT)
        {
            pwmL += corrige_vitesse(LEFT, vitesse_cible);
            pwmR += corrige_vitesse(RIGHT, -vitesse_cible);

            nbr_pulse += ENCODER_Read(LEFT);
        }
        else if (motor == LEFT)
        {
            pwmL += corrige_vitesse(LEFT, -vitesse_cible);
            pwmR += corrige_vitesse(RIGHT, vitesse_cible);

            nbr_pulse += ENCODER_Read(RIGHT);
        }
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
    * int motor: Sens de rotation
    * int angle : angle den degrés vers lequel s'orienter
    * int time : temps pour tourner
    */
void tournerSurLuiMeme(int motor, int angle, float time)
{
    float distance = arc(DISTANCEROUE / 2, angle);

    moteurInverse(motor, distance, time);
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
        //  Serial.println("Ralenti!!!");
        return vitesse - (vitesse * (pourcentage / 100));
    }
    else
    {
        return vitesse;
    }
}
