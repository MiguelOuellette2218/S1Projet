/*
* Fichier qui décris une structure vector qui permet de faire des tableau dynamique
*
*
*/
#include <Arduino.h>
#include "vector.h"

// Vider le tableau dynamique
void vector_clean(void *p)
{
    // Serial.println("clean 1");
    // Mise à zéro des taille
    ((vector *)p)->size = 0;
    ((vector *)p)->allocsize = 0;
    // Serial.println("clean 2");

    // Vider la mémoire
    free(((vector *)p)->data);
    ((vector *)p)->data = NULL;
    // Serial.println("clean 3");
}

// Réserver de l'Espace mémoire
sl vector_reserve(vector *p, ul allocsize)
{
    if (allocsize > p->allocsize)
    {
        ul newSize = 0;
        if (allocsize > p->allocsize * 2u)
        {
            newSize = allocsize;
        }
        else
        {
            newSize = ((allocsize)*3u >> 1u);
        }

        //   Serial.print("New size : ");
        //   Serial.println(newSize);
        //   Serial.print("pointer : ");
        //   Serial.println(((unsigned int)&p[0]),HEX);
        void *data = realloc(p, newSize);
        //   Serial.println("test"); // NE PAS ENLEVER

        if (data)
        {
            p->allocsize = newSize;
            p->data = (sl *)data;
        }
        else
        {
            return 0; // pas assez de mémoire
        }
    }
    return 1;
}

// Redéfinir la taille du tableau dynamique
sl vector_resize(vector *p, ul size)
{
    if (!vector_reserve(p, size * sizeof(sl)))
    {
        return 0;
    }
    else
    {
        p->size = size;
        return 1;
    }
}

// Initialisation du tableau
void vector_init(vector *p)
{
    p->data = (sl *)malloc(sizeof(sl));
    p->size = 0;
    p->allocsize = 4;
}

// Ajouter une valeur au tableau dynamique
sl vector_push(vector *p, sl x)
{
    if (!vector_resize(p, p->size + 1))
    {
        return 0;
    }
    else
    {
        p->data[p->size - 1] = x;
        return 1;
    }
}
