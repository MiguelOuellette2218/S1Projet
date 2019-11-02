#include "MyIncludes.h"

int IdentifierPossibilite(float volt)
{
/*
Possibilité possible du captage du voltage du circuit , le premier chiffre étant l'état du capteur de gauche , le 2e étant celui du milieu et le 3e etant celui du 
000 0.03 
001 1.44 
010 0.75  
011 2.16  
100 2.85
101 4.25
110 3.57
111 4.95
*/

	float possibilite[8]  = {0.03 ,1.44,0.75,2.16,2.85,4.25,3.57,4.95};

	int difference = 0.2;	

	bool capteurGauche =false;
	bool capteurMilieu = false;
	bool capteurDroit = false;

	for(unsigned int i = 0; i < sizeof(possibilite); i++)
	{
  
	    // Si le voltage entré est plus ou moin grand à chacune des possibilite 
        // (pour laisser de la place à un jeu parce que le analogue n'est pas très précis)
	    if(volt > possibilite[i]-difference && volt < possibilite[i]+difference )
	    {
	        return i;
	    }
    }

 return 10;
}


bool DecisionDirection()
{
    bool breaker = false;

    //Initialisation du pointeur récursif
    bool (*p_DecisionDirection)(void);
    p_DecisionDirection = DecisionDirection;
    
    int possibilite = IdentifierPossibilite(analogRead(A0));

    switch(possibilite)
    {
        case 0:
           //Avancer tant qu'on ne touche pas a aucune ligne (en mode H E L P)
          // Avancer(50);
            break;
       case 1:
           //TournerÀDroite
           // Tourner(45);
            break;
        case 2:
           //NePasTourner
          // Avancer(50);
            break;
        case 3:
        //Tourner(45);
           //TournerUnPeuÀDroite
            break;
        case 4:
        
        //Tourner(-45);
           //TournerAGauche
            break;
        case 5:
           //TournerEnRond
            break;
        case 6:
       // Tourner(-45);
           //TournerUnPeuAGauche
            break;
        case 7:
           //Help
            break;     
    }

}
