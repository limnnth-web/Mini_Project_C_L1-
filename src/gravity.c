#include <stdio.h>
#include <string.h>

#include "planet.h"

float calculGravity (const Planet *p)
{
    float mass;
    float rad;
    float g;

    mass = p -> massMultiplier;
    rad = p -> radiusMultiplier;

    //Le rayon et la masse doivent etre positifs
    if ((rad > 0) && (mass > 0))
    {
        //massJupiter -> massEarth
        if (strcmp(p -> massWrt, "Jupiter") == 0)
        {
            mass = mass * 317.8f;
        }

        //radJupiter -> radEarth
        if (strcmp(p -> radiusWrt, "Jupiter") == 0)
        {
            rad = rad * 11.2f;
        }
        
        //Calculer la gravite
        g = mass/(rad * rad);
        return g;
    }

    printf("Aucune donnee disponible pour le calcul\n");
    return -1.0f;
};
