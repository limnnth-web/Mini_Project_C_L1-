#include <stdio.h>
#include <string.h>
#include <time.h>

#include "modify.h"
#include "planet.h"
#include "vessel.h"


//lancer sonde
void launchVessel(Planet *catalog, int nbPlanet, int targetPlanet, Vessel *fleet, int nbVessel, char targetVessel[50])
{
    Planet *idPTarget = NULL;
    Vessel *idVTarget = NULL;

    //chercher la planete
    idPTarget = searchP(catalog, nbPlanet, targetPlanet);

    //si ne trouve pas idTarget
    if (idPTarget == NULL)
    {
        printf("Ne trouve pas cette planete\n");
        return;
    }

    //chercher le sonde
    idVTarget = searchV(fleet, nbVessel, targetVessel);

    //si ne trouve pas idVTarget
    if (idVTarget == NULL)
    {
        printf("Ne trouve pas ce sonde\n");
        return;
    }

    //changer statut
    if ((idPTarget -> statusExploration == 0) && (strcmp(idVTarget ->status, "AVAILABLE") == 0))
    {
        //planete
        idPTarget -> statusExploration = 1;
        strcpy(idPTarget -> idVessel, targetVessel);

        //sonde
        idVTarget -> idPlanet = targetPlanet;
        strcpy(idVTarget ->status, "MISSION");

        printf("La sonde %s a ete lancee vers la planete %s\n", targetVessel, idPTarget -> namePlanet);
    }
    else
    {
        printf("Le sonde %s n'est pas encore pret a etre lance ou la planete %s n'a pas statut non explorée\n", targetVessel, idPTarget -> namePlanet);
        return;
    }
};


//retourner sonde
void returnVessel(Planet *catalog, int nbPlanet, int targetPlanet, Vessel *fleet, int nbVessel, char targetVessel[50])
{   
    Planet *idPTarget = NULL;
    Vessel *idVTarget = NULL;

    //chercher le sonde
    idVTarget = searchV(fleet, nbVessel, targetVessel);

    //si ne trouve pas idVTarget
    if (idVTarget == NULL)
    {
        printf("Ne trouve pas cette sonde\n");
        return;
    }

    //chercher la planete
    idPTarget = searchP(catalog, nbPlanet, targetPlanet);

    //si ne trouve pas idTarget
    if (idPTarget == NULL)
    {
        printf("Ne trouve pas cette planete\n");
        return;
    }

    //changer statut
    if ((idPTarget -> statusExploration == 1) && (strcmp(idVTarget ->status, "MISSION") == 0))
    {
        //planete
        idPTarget -> statusExploration = 2;
        strcpy(idPTarget -> idVessel, "0");

        //sonde
        idVTarget -> idPlanet = 0;
        strcpy(idVTarget ->status, "NOT AVAILABLE");

        printf("La sonde %s est retournee de la planete %s\n", targetVessel, idPTarget -> namePlanet);
    }
    else
    {
        printf("La sonde %s n'a pas ete lancee vers la planete %s\n", targetVessel, idPTarget -> namePlanet);
        return;
    }
}

//maintenir sonde
void maintainVessel(Vessel *fleet, int nbVessel, char targetVessel[50])
{
    Vessel *idVTarget = NULL;

    idVTarget = searchV(fleet, nbVessel, targetVessel);

    if (idVTarget == NULL)
    {
        printf("Ne trouve pas cette sonde\n");
        return;
    }

    //changer status
    if (strcmp(idVTarget -> status, "NOT AVAILABLE") == 0)
    {
        strcpy(idVTarget ->status, "AVAILABLE");
        printf("La sonde %s a ete maintenu en état avec succès\n", targetVessel);
    }
    else
    {
        printf("Le sonde %s est en bon etat ou en mission\n", targetVessel);
        return;
    }
}

//add sonde
int addVessel(Vessel *fleet, int nbVessel, char targetVessel[50])
{   
    //Verifier nbV
    if (nbVessel >= maxVessel)
    {
        printf("La memoire est pleine, impossible d'ajouter une nouvelle sonde!\n");
        return nbVessel;
    }

    Vessel *idVTarget = NULL;

    //Verifier idV
    idVTarget = searchV(fleet, nbVessel, targetVessel);

    if (idVTarget != NULL)
    {
        printf("Cette sonde existe deja\n");
        return nbVessel;
    }

    //Add une sonde
    strcpy(fleet[nbVessel].idVessel, targetVessel);
    fleet[nbVessel].idPlanet = 0;
    strcpy(fleet[nbVessel].status, "AVAILABLE");

    //Ajout le nombre total des sondes
    nbVessel++;

    printf("Ajout de la sonde reussie!\n");
    return nbVessel;
}



